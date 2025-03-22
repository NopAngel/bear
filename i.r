# Define constants for system simulation
REGISTER_SIZE <- 32    # Size of the simulated register in bits
BUFFER_LIMIT <- 128    # Size of the bit buffer in bits
MEMORY_LIMIT <- 256    # Maximum memory space in bits

# Initialize system components
register <- rep(0, REGISTER_SIZE)   # Simulated register filled with zeros
bit_buffer <- c()                   # Simulated bit buffer
memory_space <- c()                 # Simulated memory

# Function to load data into the register
load_register <- function(data) {
  if (length(data) > REGISTER_SIZE) {
    stop("[ERROR] Data exceeds register size!")
  }
  register <<- c(rep(0, REGISTER_SIZE - length(data)), data) # Align data to the register
  cat("[INFO] Register loaded:", paste(register, collapse = ""), "\n")
}

# Function to transfer the register contents into the buffer
transfer_to_buffer <- function() {
  if (length(bit_buffer) + REGISTER_SIZE > BUFFER_LIMIT) {
    stop("[ERROR] Buffer overflow detected!")
  }
  bit_buffer <<- c(bit_buffer, register)
  cat("[INFO] Data transferred to buffer. Buffer size:", length(bit_buffer), "bits\n")
}

# Function to process the buffer by inverting all bits
process_buffer <- function() {
  cat("[INFO] Processing buffer...\n")
  bit_buffer <<- ifelse(bit_buffer == 0, 1, 0) # Flip bits
  cat("[INFO] Buffer processed:", paste(bit_buffer, collapse = ""), "\n")
}

# Function to write buffer data to memory
write_to_memory <- function() {
  if (length(memory_space) + length(bit_buffer) > MEMORY_LIMIT) {
    stop("[ERROR] Memory overflow detected!")
  }
  memory_space <<- c(memory_space, bit_buffer)
  bit_buffer <<- c() # Clear the buffer
  cat("[INFO] Data written to memory. Memory size:", length(memory_space), "bits\n")
}

# Function to simulate a memory dump
memory_dump <- function() {
  cat("[MEMORY DUMP] Current memory contents:\n", paste(memory_space, collapse = ""), "\n")
}

# Simulate reading binary data from a file (mock data)
read_binary_data <- function() {
  cat("[INFO] Reading binary data...\n")
  return(sample(0:1, 16, replace = TRUE)) # Generate 16 random bits for simulation
}

# Main simulation function
run_simulation <- function() {
  cat("[START] Running system simulation...\n")
  
  for (i in 1:5) { # Simulate 5 cycles of loading and processing
    data <- read_binary_data()
    cat("[CYCLE", i, "] Read data:", paste(data, collapse = ""), "\n")
    
    load_register(data)
    transfer_to_buffer()
    process_buffer()
    write_to_memory()
  }
  
  memory_dump() # Display final memory state
  cat("[END] Simulation completed successfully.\n")
}

# Run the simulation
run_simulation()
