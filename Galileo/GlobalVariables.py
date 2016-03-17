udp_receive_port = 5625

server_url = "http://localhost/lockotron/public_html"
gp_path = "/sys/class/gpio/"

model = 'faces.xml'
frame = 'frame.jpg'
update = 'new-faces.xml'

# OUTPUTS
doorLock_Led = 13
motion_Led = 12
recognizer_Led = 11

# INPUTS
motion_Sensor = 2

# PRIORITIES
udp_server_priority = 60
face_recognizer_priority = 50
main_script_priority = 55
