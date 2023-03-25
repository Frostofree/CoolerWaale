from ._anvil_designer import SetUpTemplate
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
  anvil.server.call("create_ae", uri_cse, ae)
  uri_ae.append(uri_cse + "/" + ae)

for i in uri_ae:
  anvil.server.call("create_cnt", i, cnt)
  uri_cnt.append(i + "/" + cnt)
  print(i)
  
anvil.server.call("create_cnt", uri_ae[0], "Humidity_Threshold")
uri_cnt_hThres = uri_ae[0] + "/" + "Humidity_Threshold"
  
anvil.server.call("create_cnt", uri_ae[1],"Temp_Low")
uri_cnt_TL = uri_ae[1] + "/" + "Temp_Low"

anvil.server.call("create_cnt", uri_ae[1],"Temp_Medium")
uri_cnt_TM = uri_ae[1] + "/" + "Temp_Medium"

anvil.server.call("create_cnt", uri_ae[1],"Temp_High") 
uri_cnt_TM = uri_ae[1] + "/" + "Temp_High"


class SetUp(SetUpTemplate):
  def __init__(self, **properties):
    # Set Form properties and Data Bindings.
    self.init_components(**properties)

    # Any code you write here will run before the form opens.
    

  def button_1_click(self, **event_args):
    """This method is called when the button is clicked"""
    open_form('Form1')
    pass

