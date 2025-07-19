#!/usr/bin/perl
use strict;
use warnings;

# Mock system constants
my $REGISTER_SIZE = 64;  # Register size in bits
my $BUFFER_LIMIT = 512;  # Buffer size in bits
my $MEMORY_BLOCK_SIZE = 128;  # Memory block size in bits
my $FILE_BLOCK_SIZE = 64;  # File block size in bits
my $PROCESS_COUNT = 4;  # Simulated number of processes

# Initialize simulated system components
my @bit_buffer = ();
my @memory_space = ();
my %process_table = ();
my %file_system = (
    "kernel.sys" => "101100110011001010101010111100001010101011110000",
    "config.cfg" => "001101010101011100101010101011110011010101011100",
    "userdata.dat" => "111000111000111111000111000111111110001110001111",
    "driver.bin" => "110011001100110011001100110011001100110011001100"
);
my $register = "0" x $REGISTER_SIZE;

# Function to load data into the register
sub load_register {
    my ($data) = @_;
    if (length($data) > $REGISTER_SIZE) {
        die "[ERROR] Data exceeds the register size ($REGISTER_SIZE bits).\n";
    }
    for my $bit (split //, $data) {
        if ($bit !~ /^[01]$/) {
            die "[ERROR] Invalid binary data detected.\n";
        }
    }
    $register = substr("0" x $REGISTER_SIZE . $data, -$REGISTER_SIZE);
    print "[INFO] Register loaded: $register\n";
}

# Function to transfer register contents to buffer
sub transfer_to_buffer {
    if (scalar(@bit_buffer) + $REGISTER_SIZE > $BUFFER_LIMIT) {
        die "[ERROR] Buffer overflow detected. Cannot transfer data.\n";
    }
    push @bit_buffer, split //, $register;
    print "[INFO] Register contents transferred to buffer. Buffer size: " . scalar(@bit_buffer) . " bits.\n";
}

# Function to process buffer (e.g., bitwise encryption)
sub process_buffer {
    print "[INFO] Processing buffer...\n";
    for my $i (0 .. $#bit_buffer) {
        $bit_buffer[$i] = $bit_buffer[$i] eq "1" ? "0" : "1";  # Invert bits
    }
    print "[INFO] Buffer processed. Current state: " . join("", @bit_buffer) . "\n";
}

# Function to write processed data to memory
sub write_to_memory {
    if (scalar(@memory_space) + scalar(@bit_buffer) > $MEMORY_BLOCK_SIZE) {
        die "[ERROR] Memory overflow detected. Cannot write data.\n";
    }
    push @memory_space, @bit_buffer;
    @bit_buffer = ();  # Clear buffer after writing to memory
    print "[INFO] Data written to memory. Memory size: " . scalar(@memory_space) . " bits.\n";
}

# Function to simulate process management
sub initialize_process_table {
    for my $pid (1 .. $PROCESS_COUNT) {
        $process_table{$pid} = {
            "state" => "ready",
            "priority" => int(rand(10)),
            "cpu_time" => 0,
        };
        print "[DEBUG] Process $pid initialized: " . join(", ", map { "$_=$process_table{$pid}->{$_}" } keys %{$process_table{$pid}}) . "\n";
    }
}

# Function to simulate context switching
sub context_switch {
    my ($current_pid, $next_pid) = @_;
    if (!exists $process_table{$current_pid} || !exists $process_table{$next_pid}) {
        die "[ERROR] Invalid process IDs specified for context switch.\n";
    }
    $process_table{$current_pid}->{state} = "waiting";
    $process_table{$next_pid}->{state} = "running";
    print "[INFO] Context switched: Process $current_pid -> Process $next_pid\n";
}

# Function to read file data and split into blocks
sub read_file_data {
    my ($filename) = @_;
    if (!exists $file_system{$filename}) {
        die "[ERROR] File '$filename' not found.\n";
    }
    print "[INFO] Reading file '$filename'...\n";
    return ($file_system{$filename} =~ /.{1,$FILE_BLOCK_SIZE}/g);
}

# Function to simulate memory dump
sub memory_dump {
    print "[MEMORY DUMP] Current memory contents: " . join("", @memory_space) . "\n";
}

# Function to simulate logging system operations
sub log_event {
    my ($event_type, $message) = @_;
    open my $logfile, '>>', 'system.log' or die "[ERROR] Cannot open log file.\n";
    print $logfile "[$event_type] $message\n";
    close $logfile;
    print "[LOG] $message\n";
}

# Main simulation routine
sub run_kernel_simulation {
    print "[START] Kernel simulation initiated...\n";

    # Initialize processes
    log_event("INFO", "Initializing process table...");
    initialize_process_table();

    # Read data from file and process it
    my @data_blocks = read_file_data("kernel.sys");
    for my $block (@data_blocks) {
        print "[DEBUG] Processing block: $block\n";
        load_register($block);
        transfer_to_buffer();
        process_buffer();
        write_to_memory();
    }

    # Simulate context switching
    log_event("INFO", "Simulating process context switching...");
    context_switch(1, 2);

    # Perform memory dump
    log_event("INFO", "Performing memory dump...");
    memory_dump();

    print "[END] Kernel simulation completed successfully.\n";
}

# Execute the kernel simulation
run_kernel_simulation();
