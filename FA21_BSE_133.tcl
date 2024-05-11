
set val(stop)   10.0                         ;# time of simulation end

#Create a ns simulator
set ns [new Simulator]

#Open the NS trace file
set tracefile [open out.tr w]
set f0 [open out0.tr w]
set f1 [open out1.tr w]
set f2 [open out2.tr w]
$ns trace-all $tracefile

#Open the NAM trace file
set namfile [open out.nam w]
$ns namtrace-all $namfile
$ns rtproto DV

#Create 16 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]
set n12 [$ns node]
set n13 [$ns node]
set n14 [$ns node]
set n15 [$ns node]

#Createlinks between nodes
$ns duplex-link $n0 $n1 100.0Mb 10ms DropTail
$ns queue-limit $n0 $n1 50
$ns duplex-link $n1 $n2 100.0Mb 10ms DropTail
$ns queue-limit $n1 $n2 50
$ns duplex-link $n2 $n3 100.0Mb 10ms DropTail
$ns queue-limit $n2 $n3 50
$ns duplex-link $n3 $n7 100.0Mb 10ms DropTail
$ns queue-limit $n3 $n7 50
$ns duplex-link $n7 $n11 100.0Mb 10ms DropTail
$ns queue-limit $n7 $n11 50
$ns duplex-link $n11 $n15 100.0Mb 10ms DropTail
$ns queue-limit $n11 $n15 50
$ns duplex-link $n15 $n14 100.0Mb 10ms DropTail
$ns queue-limit $n15 $n14 50
$ns duplex-link $n14 $n13 100.0Mb 10ms DropTail
$ns queue-limit $n14 $n13 50
$ns duplex-link $n13 $n12 100.0Mb 10ms DropTail
$ns queue-limit $n13 $n12 50
$ns duplex-link $n12 $n8 100.0Mb 10ms DropTail
$ns queue-limit $n12 $n8 50
$ns duplex-link $n8 $n4 100.0Mb 10ms DropTail
$ns queue-limit $n8 $n4 50
$ns duplex-link $n4 $n0 100.0Mb 10ms DropTail
$ns queue-limit $n4 $n0 50
$ns duplex-link $n0 $n5 100.0Mb 10ms DropTail
$ns queue-limit $n0 $n5 50
$ns duplex-link $n5 $n10 100.0Mb 10ms DropTail
$ns queue-limit $n5 $n10 50
$ns duplex-link $n10 $n15 100.0Mb 10ms DropTail
$ns queue-limit $n10 $n15 50
$ns duplex-link $n3 $n6 100.0Mb 10ms DropTail
$ns queue-limit $n3 $n6 50
$ns duplex-link $n6 $n9 100.0Mb 10ms DropTail
$ns queue-limit $n6 $n9 50
$ns duplex-link $n9 $n12 100.0Mb 10ms DropTail
$ns queue-limit $n9 $n12 50

#Give node position (for NAM)
$ns duplex-link-op $n0 $n1 orient left-down
$ns duplex-link-op $n1 $n2 orient left-down
$ns duplex-link-op $n2 $n3 orient left-down
$ns duplex-link-op $n3 $n7 orient right
$ns duplex-link-op $n7 $n11 orient right
$ns duplex-link-op $n11 $n15 orient right
$ns duplex-link-op $n15 $n14 orient right-up
$ns duplex-link-op $n14 $n13 orient right-up
$ns duplex-link-op $n13 $n12 orient right-up
$ns duplex-link-op $n12 $n8 orient left

$ns duplex-link-op $n8 $n4 orient left

$ns duplex-link-op $n4 $n0 orient left

$ns duplex-link-op $n0 $n5 orient right-down
$ns duplex-link-op $n5 $n10 orient right-down
$ns duplex-link-op $n10 $n15 orient right-down
$ns duplex-link-op $n3 $n6 orient right-up
$ns duplex-link-op $n6 $n9 orient right-up
$ns duplex-link-op $n9 $n12 orient right-up

#===================================
#        Agents Definition        
#===================================
#Setup a UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n4 $udp0
set null1 [new Agent/Null]
$ns attach-agent $n8 $null1
$ns connect $udp0 $null1
$udp0 set packetSize_ 1500

#Setup a TCP connection
set tcp3 [new Agent/TCP]
$ns attach-agent $n0 $tcp3
set sink4 [new Agent/TCPSink]
$ns attach-agent $n12 $sink4
$ns connect $tcp3 $sink4
$tcp3 set packetSize_ 1500

#Setup a TCP connection
set tcp11 [new Agent/TCP]
$ns attach-agent $n4 $tcp11
set sink12 [new Agent/TCPSink]
$ns attach-agent $n11 $sink12
$ns connect $tcp11 $sink12
$tcp11 set packetSize_ 1500

#Setup a TCP connection
set tcp13 [new Agent/TCP]
$ns attach-agent $n8 $tcp13
set sink14 [new Agent/TCPSink]
$ns attach-agent $n7 $sink14
$ns connect $tcp13 $sink14
$tcp13 set packetSize_ 1500

#Setup a TCP connection
set tcp15 [new Agent/TCP]
$ns attach-agent $n0 $tcp15
set sink16 [new Agent/TCPSink]
$ns attach-agent $n15 $sink16
$ns connect $tcp15 $sink16
$tcp15 set packetSize_ 1500

#Setup a TCP connection
set tcp17 [new Agent/TCP]
$ns attach-agent $n12 $tcp17
set sink18 [new Agent/TCPSink]
$ns attach-agent $n3 $sink18
$ns connect $tcp17 $sink18
$tcp17 set packetSize_ 1500


set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 1.0Mb
$cbr0 set random_ null
$ns at 1.0 "$cbr0 start"
$ns at 2.0 "$cbr0 stop"

#Setup a CBR Application over TCP connection
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $tcp3
$cbr1 set packetSize_ 1000
$cbr1 set rate_ 1.0Mb
$cbr1 set random_ null
$ns at 0.0 "$cbr1 start"
$ns at 2.0 "$cbr1 stop"

#Setup a CBR Application over TCP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $tcp11
$cbr2 set packetSize_ 1000
$cbr2 set rate_ 1.0Mb
$cbr2 set random_ null
$ns at 0.0 "$cbr2 start"
$ns at 2.0 "$cbr2 stop"

#Setup a CBR Application over TCP connection
set cbr3 [new Application/Traffic/CBR]
$cbr3 attach-agent $tcp13
$cbr3 set packetSize_ 1000
$cbr3 set rate_ 1.0Mb
$cbr3 set random_ null
$ns at 0.0 "$cbr3 start"
$ns at 2.0 "$cbr3 stop"

#Setup a CBR Application over TCP connection
set cbr4 [new Application/Traffic/CBR]
$cbr4 attach-agent $tcp15
$cbr4 set packetSize_ 1000
$cbr4 set rate_ 1.0Mb
$cbr4 set random_ null
$ns at 0.0 "$cbr4 start"
$ns at 2.0 "$cbr4 stop"

#Setup a CBR Application over TCP connection
set cbr5 [new Application/Traffic/CBR]
$cbr5 attach-agent $tcp17
$cbr5 set packetSize_ 1000
$cbr5 set rate_ 1.0Mb
$cbr5 set random_ null
$ns at 0.0 "$cbr5 start"
$ns at 2.0 "$cbr5 stop"
#$ns at $delay "$link down"

#Define a 'finish' procedure
proc finish {} {
    global ns tracefile namfile
    $ns flush-trace
    close $tracefile
    close $namfile
    exec nam out.nam &
    exec xgraph out0.tr out1.tr out2.tr -geometry 800x400 &
    exit 0
}

#Plot xgraph
proc record {} {
 global sink4 sink12 sink14 f0 f1 f2
 #Get an instance of the simulator
 set ns [Simulator instance]
 #Set the time after which the procedure should be called again
 set time 0.5
 #How many bytes have been received by the traffic sinks?
 set bw0 [$sink4 set bytes_]
 set bw1 [$sink12 set bytes_]
 set bw2 [$sink14 set bytes_]
 #Get the current time
 set now [$ns now]
 #Calculate the bandwidth (in MBit/s) and write it to the files
 puts $f0 "$now [expr $bw0/$time*8/1000000]"
 puts $f1 "$now [expr $bw1/$time*8/1000000]"
 puts $f2 "$now [expr $bw2/$time*8/1000000]"
 #Reset the bytes_ values on the traffic sinks
 $sink4 set bytes_ 0
 $sink12 set bytes_ 0
 $sink14 set bytes_ 0
 #Re-schedule the procedure
 $ns at [expr $now+$time] "record"
}

$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "finish"
$ns at $val(stop) "puts \"done\" ; $ns halt"
$ns run

