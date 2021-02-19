import socket
from spidev import SpiDev

class SPI2ADC:
	def __init__(self, bus=0, device=0):
		self.bus = bus
		self.device = device
		self.spi = SpiDev()
		self.open()

	def open(self):
		self.spi.open(self.bus, self.device)
		self.spi.max_speed_hz = 1000000

	def read(self, channel = 0):
		adc = self.spi.xfer([0xbe, 0xef])
		#adc = self.spi.xfer2([0x01, 0x08, 0])
		#data = ((adc[1] & 3) << 8) + adc[2]
		return adc
		#return data

	def close(self):
		self.spi.close()

class CommandDataConnection:
	def __init__(self, server_addr, server_port, connection_timeout):
		self.server_addr = server_addr
		self.server_port = server_port
		self.connection_timeout = connection_timeout
		self.send_interval = 1000

	def open(self):
		if this.client:
			this.client.close()
		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.client.connect((self.server_addr, self.server_port))
	
	def execute_command(command, data):
		if command == SA_CMD_NULL:
			return
		if command == SA_CMD_OFF:
			turn_relay_off()
			return
		if command == SA_CMD_ON:
			turn_relay_on()
			return
		if command == SA_CMD_INT:
			this.send_interval = data
 

	def send_packet(packet):
		pass

	def send_id_message(id):
		pass

	def send_current_message(current):
		pass
		

SA_CMD_NULL = 0x00
SA_CMD_OFF = 0x01
SA_CMD_ON = 0x02
SA_CMD_INT = 0x03

AS_CMD_NULL = 0x00
AS_CMD_CUR = 0x01
AS_CMD_ID = 0x02

SERVER_ADDR = '192.168.1.199'
SERVER_PORT = 5942
CONNECT_TIMEOUT = 1000

def turnRelayOn():
	#Put some code here
	pass

def turnRelayOff():
	#Put some code here
	pass

adc = SPI2ADC()
connection = CommandDataConnection(SERVER_ADDR, SERVER_PORT, CONNECT_TIMEOUT)

while True:
	current = adc.read()
	if(current != 0):
		print(current)
	#connection.send_current_message(current)

