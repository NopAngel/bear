
use strict;


my @kernel_panic_errors = (
    "Unable to mount root filesystem",
    "No init found – Cannot locate initial system process",
    "CPU Exception in kernel mode",
    "Kernel stack corruption detected",
    "Double fault exception – Nested processor fault",
    "Machine check exception – Hardware-level CPU error",
    "NULL pointer dereference in kernel space",
    "Page fault in kernel mode – Invalid memory access",
    "General protection fault in kernel mode",
    "Out of memory (OOM) – System memory exhaustion",
    "Critical kernel module loading failure",
    "Unrecoverable hardware IRQ error",
    "Critical I/O error – Disk operation failure",
    "Kernel data structure corruption",
    "Critical filesystem corruption detected",
);

foreach my $error (@kernel_panic_errors) {
    print "$error\n";
}
