from ._anvil_designer import Form1Template
from anvil import *
import anvil.tables as tables
import anvil.tables.query as q
from anvil.tables import app_tables
import anvil.server

uri_cse = "https://638b-2409-4070-2d9a-b8fc-e117-98d6-c434-f010.in.ngrok.io/~/in-cse/in-name"
aeList = ["Humidity", "Temperature", "WaterLevel", "Mode", "FanSpeed", "Pump"]
cnt="node1"
uri_ae = []
uri_cnt = []

for ae in aeList:
  uri_ae.append(uri_cse + "/" + ae)

for i in uri_ae:
  uri_cnt.append(i + "/" + cnt)
  
uri_cnt_hThres = uri_ae[0] + "/" + "Humidity_Threshold"
  
uri_cnt_TL = uri_ae[1] + "/" + "Temp_Low"

uri_cnt_TM = uri_ae[1] + "/" + "Temp_Medium"

uri_cnt_TH = uri_ae[1] + "/" + "Temp_High"


class Form1(Form1Template):
  def __init__(self, **properties):
    # Set Form properties and Data Bindings.
    self.init_components(**properties)
    
    # Any code you write here will run before the form opens.
    
  def Manual_clicked(self, **event_args):
    """This method is called when this radio button is selected"""
    anvil.server.call("create_data_cin", uri_cnt[3] , "m")
    open_form('Form2')
    get_open_form().Manual.selected = True
    pass

  def Automatic_clicked(self, **event_args):
    anvil.server.call("create_data_cin", uri_cnt[3] , "a")
    open_form('Form1')
    get_open_form().Automatic.selected = True
    """This method is called when this radio button is selected"""
    pass

  def button_1_click(self, **event_args):
    """This method is called when the button is clicked"""
    anvil.server.call("create_data_cin", uri_cnt_hThres , self.text_box_1.text)
    anvil.server.call("create_data_cin", uri_cnt_TL , self.text_box_2.text)
    anvil.server.call("create_data_cin", uri_cnt_TM , self.text_box_3.text)
    anvil.server.call("create_data_cin", uri_cnt_TH , self.text_box_4.text)
    pass

  def button_2_click(self, **event_args):
#     content = []
#     for i in uri_ae:
#       response = anvil.server.call("get_data", i + "/node1?rcn=4")
#       print(response)
#       content.append([])
#       for data in response["m2m:cnt"]["m2m:cin"][-20:]:
#           content[-1].append(data["con"])                
    content = []
    for i in uri_ae:
      response2 = anvil.server.call("get_data", i + "/node1/la")
#       print(response2)  
      content.append(response2['m2m:cin']['con'])
    s = ""
    if(content[5] == "T"):
        s = "ON"
    else:
        s = "OFF"
    self.rich_text_9.content = "# Humidity: \t\t{}".format(content[0])
    self.rich_text_7.content = "# Temperature: \t\t{}".format(content[1])
    self.rich_text_6.content = "# Water Level: \t\t{}".format(content[2])
    self.rich_text_8.content = "# Fan Speed: \t\t{}".format(content[4])
    self.rich_text_10.content = "# Pump: \t\t{}".format(s)
    pass





