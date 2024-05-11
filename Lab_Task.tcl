set ns [new Simulator]

# Open the NAM trace file 
set nf [open out.nam w] 
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    # Close the NAM trace file
    close $nf
    # Execute NAM on the trace file
    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 2Mb 10ms RED
$ns duplex-link $n2 $n3 1.7Mb 20 ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail

# Attach UDP and Null to n1
set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n1 $null0

# Attach CBR to n1
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packet_size_ 1Kb
$cbr0 set rate_ 1mb 
$cbr0 attach-agent $udp0

# Attach TCP and Null to n0
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set null1 [new Agent/Null]
$ns attach-agent $n0 $null1

# Attach FTP to n0
set ftp0 [new Application/FTP]
$ns attach-agent $n0 $ftp0

# Attach Null to n3
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

$ns connect $tcp0 $null3
# $ns connect $udp0 $udp1  ; Commented out since udp1 is not defined
$ns connect $udp0 $null3

$ns at 0 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"
$ns at 0 "$ftp0 start"
$ns at 4.5 "$ftp0 stop"

$ns at 5.0 "finish"
$ns run

