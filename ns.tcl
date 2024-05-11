set ns [new Simulator]

#Open the NAM trace file 
set nf [open out.nam w] 
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    #Close the NAM trace file
    close $nf
    #Execute NAM on the trace file
    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 2Mb 10ms DropTail

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n0 $null0

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set null1 [new Agent/Null]
$ns attach-agent $n1 $null1

$ns connect $udp0 $null1
# $ns connect $udp0 $udp1
$ns connect $udp1 $null0



set cbr0 [new Application/Traffic/CBR]
$cbr0 set packet_size_ 1000 
$cbr0 set rate_ 1mb 
$cbr0 attach-agent $udp0

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packet_size_ 1000 
$cbr1 set rate_ 1mb 
$cbr1 attach-agent $udp1

$ns at 0 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"
$ns at 0 "$cbr1 start"
$ns at 4.5 "$cbr1 stop"

$ns at 5.0 "finish"
$ns run