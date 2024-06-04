import requests

NODERED_URL = 'http://localhost:1880'

"""
Calls the Node-Red http in to launch irrigation
"""
def irrigate():
    data = {"irrigate": True}
    response = requests.post(f'{NODERED_URL}/controls', json=data)
    return response.json()