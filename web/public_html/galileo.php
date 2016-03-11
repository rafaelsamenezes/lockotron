<?php
$galileo_ip = "10.42.0.252";

if (isset($_GET['panic']) || isset($_GET['panic'])) {
    $msg = 0;
} elseif (isset($_GET['update']) || isset($_GET['update'])) {
    $msg = 1;
} elseif (isset($_GET['kill']) || isset($_GET['kill'])) {
    $msg = 3;
} else {
    http_response_code(500);
    exit();
}
$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
if ($socket) {
    $packet = pack("C", $msg);
    socket_sendto($socket, $packet, 1, 0, $galileo_ip, "5625");
}
