#Create a ns simulator
set ns [new Simulator]

#Open the NS trace file
set tracefile [open out.tr w]
$ns trace-all $tracefile

#Open the NAM trace file
set namfile [open out.nam w]
$ns namtrace-all $namfile


proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam out.nam &
    exit 0
}

#Create 10 nodes
#create nodes,set distance and queue limit
for {set i 0} {$i < 10} {incr i} {
   set n($i) [$ns node]
   $n($i) set X [expr $i * 150]
}

#create links
for {set i 0} {$i < 9} {incr i} {
 $ns duplex-link $n($i) $n([expr $i+1]) 1Mb 10ms DropTail
 $ns duplex-link-op $n($i) $n([expr $i+1]) orient right
 $ns queue-limit $n($i) $n([expr $i+1]) 50
}

# Setup a CBR Application over TCP connection
set window_size 8
set tcp [new Agent/TCP]
$tcp set window_ $window_size
$ns attach-agent $n(3) $tcp

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 1460
$cbr set rate_ 4.0Mb
$cbr attach-agent $tcp

set null [new Agent/TCPSink]
$ns attach-agent $n(4) $null

$ns connect $tcp $null

# Start and stop the application
$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"

$ns at 5.0 "finish"
$ns run
