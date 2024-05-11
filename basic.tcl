# Create a simulator object
set ns [new Simulator]

# Create two nodes
set n1 [$ns node]
set n2 [$ns node]

# Create a link between nodes
$ns duplex-link $n1 $n2 10Mb 10ms DropTail

# Create a TCP traffic source at node 1
set tcp [new Agent/TCP]
set ftp [new Application/Traffic/FTP]
$ftp attach-agent $tcp
$ns attach-agent $n1 $tcp

# Create a TCP traffic sink at node 2
set null [new Agent/Null]
$ns attach-agent $n2 $null

# Connect the traffic source to the sink
$ns connect $tcp $null

# Set simulation end time
$ns at 5.0 "$ns stop"

# Run the simulation
$ns run

