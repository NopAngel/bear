# Constants for the simulated system
REGISTER_SIZE <- 64         # Size of each register in bits
BUFFER_LIMIT <- 512         # Maximum size of the bit buffer in bits
MEMORY_LIMIT <- 1024        # Maximum memory space in bits
NUM_REGISTERS <- 4          # Number of simulated registers
EVENT_LOG_SIZE <- 50        # Maximum size of the system event log
PROCESS_LIMIT <- 5          # Number of processes to simulate

# Initialize system components
registers <- matrix(0, nrow = NUM_REGISTERS, ncol = REGISTER_SIZE)  # Multiple registers
bit_buffer <- c()                                                  # Bit buffer
memory_space <- c()                                                # Simulated memory space
event_log <- c()                                                   # Event log for system messages
process_table <- list()                                            # Process table

# Function to log events in the system log
log_event <- function(event_type, message) {
  if (length(event_log) >= EVENT_LOG_SIZE) {
    event_log <<- event_log[-1] # Remove the oldest log to keep the log size within the limit
  }
  timestamp <- Sys.time()
  event <- paste("[", event_type, "]", timestamp, "-", message)
  event_log <<- c(event_log, event)
  cat(event, "\n")
}

# Function to load binary data into a specific register
load_register <- function(register_id, data) {
  if (register_id > NUM_REGISTERS || register_id <= 0) {
    stop("[ERROR] Invalid register ID!")
  }
  if (length(data) > REGISTER_SIZE) {
    log_event("ERROR", "Data exceeds register size.")
    stop("[ERROR] Data exceeds register size!")
  }
  registers[register_id, ] <<- c(rep(0, REGISTER_SIZE - length(data)), data)
  log_event("INFO", paste("Register", register_id, "loaded with data:", paste(data, collapse = "")))
}

# Function to transfer register data to the buffer
transfer_to_buffer <- function(register_id) {
  if (length(bit_buffer) + REGISTER_SIZE > BUFFER_LIMIT) {
    log_event("ERROR", "Buffer overflow detected during data transfer.")
    stop("[ERROR] Buffer overflow detected!")
  }
  bit_buffer <<- c(bit_buffer, registers[register_id, ])
  log_event("INFO", paste("Register", register_id, "data transferred to buffer. Buffer size:", length(bit_buffer), "bits."))
}

# Function to process the buffer (invert bits and count ones)
process_buffer <- function() {
  if (length(bit_buffer) == 0) {
    log_event("WARNING", "Attempted to process an empty buffer.")
    stop("[ERROR] Buffer is empty!")
  }
  log_event("INFO", "Processing buffer...")
  ones_count <- sum(bit_buffer) # Count the number of ones
  bit_buffer <<- ifelse(bit_buffer == 0, 1, 0) # Flip all bits
  log_event("INFO", paste("Buffer processed. Ones flipped:", ones_count, "/", length(bit_buffer)))
}

# Function to write buffer data to memory
write_to_memory <- function() {
  if (length(memory_space) + length(bit_buffer) > MEMORY_LIMIT) {
    log_event("ERROR", "Memory overflow detected during write operation.")
    stop("[ERROR] Memory overflow detected!")
  }
  memory_space <<- c(memory_space, bit_buffer)
  bit_buffer <<- c() # Clear the buffer
  log_event("INFO", paste("Buffer written to memory. Current memory size:", length(memory_space), "bits."))
}

# Function to simulate a memory dump
memory_dump <- function() {
  log_event("INFO", "Performing memory dump...")
  if (length(memory_space) == 0) {
    cat("[MEMORY DUMP] Memory is empty.\n")
  } else {
    cat("[MEMORY DUMP] Current memory contents:\n", paste(memory_space, collapse = ""), "\n")
  }
}

# Function to simulate system statistics
system_stats <- function() {
  log_event("INFO", "Collecting system statistics...")
  stats <- list(
    registers_in_use = NUM_REGISTERS,
    buffer_size = length(bit_buffer),
    memory_used = length(memory_space),
    memory_remaining = MEMORY_LIMIT - length(memory_space)
  )
  cat("[SYSTEM STATS]\n")
  print(stats)
}

# Function to initialize process table
initialize_process_table <- function() {
  for (i in 1:PROCESS_LIMIT) {
    process_table[[i]] <<- list(
      pid = i,
      state = "ready",
      priority = sample(1:10, 1),
      runtime = 0
    )
    log_event("INFO", paste("Process", i, "initialized with priority", process_table[[i]]$priority))
  }
}

# Function to simulate process scheduling
schedule_processes <- function() {
  log_event("INFO", "Starting process scheduling...")
  for (i in 1:PROCESS_LIMIT) {
    process_table[[i]]$state <<- "running"
    process_table[[i]]$runtime <<- process_table[[i]]$runtime + 1
    log_event("DEBUG", paste("Process", process_table[[i]]$pid, "is running. Total runtime:", process_table[[i]]$runtime))
    process_table[[i]]$state <<- "waiting"
  }
}

# Function to simulate reading binary data (mock input)
read_binary_data <- function() {
  log_event("INFO", "Reading binary data...")
  return(sample(0:1, sample(8:32, 1), replace = TRUE)) # Generate random binary data
}

# Main kernel simulation routine
run_kernel_simulation <- function() {
  log_event("START", "Kernel simulation initiated.")

  # Initialize processes
  initialize_process_table()

  # Simulate several system cycles
  for (cycle in 1:5) {
    log_event("CYCLE", paste("Starting system cycle", cycle))
    for (register_id in 1:NUM_REGISTERS) {
      data <- read_binary_data()
      load_register(register_id, data)
      transfer_to_buffer(register_id)
    }
    process_buffer()
    write_to_memory()
  }

  # Display statistics and perform a memory dump
  system_stats()
  memory_dump()

  # Simulate process scheduling
  schedule_processes()

  log_event("END", "Kernel simulation completed successfully.")
}

# Run the simulation
run_kernel_simulation()
