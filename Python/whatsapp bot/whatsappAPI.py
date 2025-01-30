# Funcionamento: Recebe um request da API direcionada a um servidor flask, que processa esse request e inicia um chat.
# LEMBRETE: IMPLEMENTAR LIMITE DE TEMPO

from flask import Flask, request, jsonify
import os
import queue
import requests

# Variáveis globais
app = Flask(__name__)
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Flask Config
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def send(numero, text, opt=None):
    # URL da API para envio, apenas de exemplo
    url = "https://api.z-api.io/instances/3D654E85F0B83013B53D5A11DC8EC207/token/4E64C6A4CC1C711A7B677B92/send-text"
    
    match opt:
        
        #Caso jsonify não funcione, delete a linha e a # do comentário acima dela
        case None:
            #payload = "{\"phone\": \""+numero+"\", \"message\": \""+text+"\"}"
            payload = jsonify({'phone': numero, 'message': text})
        case "poll":
            #payload = "{\"phone\": \""+numero+"\", \"message\": \""+text+"\", \"pollMaxOptions\": \"1\", \"poll\": [ { \"name\": \"Opt1\" }, { \"name\": \"Opt2\" }]}"
            payload = jsonify({'phone': numero, 'message': text, 'poolMaxOptions': '1', 'poll': [{'name': 'Opt1', 'name': 'Opt2'}]})
    
    headers = {'Content-Type': "application/json", 'client-token': 'F76d169568bb0450d89fe2f4c0aa636f9S'}

    response = requests.request("POST", url, data=payload, headers=headers)
    print(response.text)


@app.route("/", methods=["POST"])
def received():
    GatheredResponse = request.get_json()
    print(request.get_json())
    if GatheredResponse["fromApi"] == False:
        phone = GatheredResponse["phone"]
        from_me = GatheredResponse["fromMe"]
        # O que acontecerá após uma mensagem recebida
        
    return 200, ' '
    
def main():
    # Clear Screen
    os.system("cls")
    app.run()
    
main()