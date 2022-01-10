################################################################################################################
##                                        CODIGO CREAR NUESTRA RED NEURONAL                                   ##
## 		Nuestras red neuronal tendra que aprender la tarea de conducir un cochecito 		                  ##
## 		Que posee de entrada 3 sensores de ultrasonidos y tiene que controlar 4 motores D.C                   ##
## 		                                                                                                      ##
################################################################################################################
import numpy as np


#Funcion oculta de activacion.
#Variable sigm con funciones ocultas, con la finalidad de tener en una misma variable tener una funcion deseada y su derivada.
sigm = (lambda x: 1 / (1 + np.e **(-x)), #Funcion sigmoide.
	lambda x: x * (1 - x))		 #Funcion derivada de la funcion sigmoide.

relu = lambda x: np.maximum(0, x)	 #Funcion Relu.

#Funcion oculta de activacion.
tanh = (lambda x: np.tanh(x),
	lambda x: 1.0 - x**2)

#Funcion oculta de coste.
l2_cost = (lambda Yp, Yr: np.mean((Yp - Yr) ** 2), #Error cuadratico Medio.
	   lambda Yp, Yr: (Yp - Yr))		   #Derivada de la funcion de coste.


#Clase que sirve para crear las diferentes capas de nuestra red.
class NeuralNetwork:
#Funcion que inicializa a nuestra clase neuronal_layer.
	#Funcion que inicializa a nuestra clase neuronal_layer.
	def __init__(self, n_conn, n_neur, act_f):		#Introducimos numero de conexiones, numero de neuronas en la capa y la funcion de activacion.

		self.act_f = act_f 				#Funcion de activacion
		self.b = np.random.rand(1, n_neur) * 2 - 1 	#Parametro de Byes.
		self.W = np.random.rand(n_conn, n_neur) * 2 - 1 #Matriz de pesos donde el rango de pesos varia entre (-1,1)
		#print("Vamos a aver:", np.random.rand(n_conn, n_neur) * 2 - 1 )


#Funcion para crear la red neuronal, donde recoge como paratmetros, 
#la topologia de nuestra red, y la funcion de activacion que tendran 
#todas las capas.No es necesario que cada capa tenga la misma funcion
#de activacion, en este caso se realizara asi por simplicidad.
def create_nn(topology, act_f):
	nn = [] #Vector que contendra todas las capas de nuestra red, este vector contendra toda la estructura de nuestra red.

	for l, layer in enumerate(topology[:-1]): 			     #Recojemos el indice y el objeto del vector topology 										      en "l" y "layer"
		nn.append(NeuralNetwork(topology[l], topology[l+1], act_f)) #Se añade una capa nueva a la estructura de red.
	#return nn 		

	#print("longitud de nn:", len(nn))					     #Devolvemos la estructura de la red neuronal
	#for k, layer in enumerate(nn):
	#	print("Pesos de la capa numero:", k)
	#	print(nn[k].W)
	return nn 
	


#Ahora toca entrenar a nuestra red neuronal, para esta tarea creamos la funcion de entrenamiento para posteriormente entrenar a nuestra red llamando a dicha funcion..
#Funcion de entrenamiento donde recibe como parametros nuestra red neuronal, Datos de entrada, Datos de salida, funcion de coste y learning rate "ratio de aprendizaje" para el descenso del gradinte.
#Se puede elegir si realizar un entrenamiento de  uestra Red Neuronal o simplemente obtener una prediccion, dependiendo del valor de la variable booleana "train" si "train==True" se realiza un entrenamiento si es "train==False" se realiza una simple prediccion.
#"X" Matriz de datos de entrada, "Y" Matriz de datos de salida.
# "lr" Learning Rate o rango de aprendizaje.  
def train( neural_net, X, Y, l2_cost, lr=0.5,train = True):
	
	out = [(None, X)] #Par de datos para referirse a la primera capa de entrada donde la suma ponderada no existe y el output de la capa de entrada es el vector "X"
			  #En las siguientes pasadas dentro del bucle los pares datos seran la suma ponderda y la funcion de activacion de la capa en que se encuentre el bucle.
	#print(out[-1][1])

#Forwrad Pass
##En forward Pass cada neurona realiza una suma ponderada donde multiplica el peso de sus conexiones con el valor de entrada que recibe, a esto le suma el parametro de bies o sesgo. Al realizar esta operacion cada neurona esta realizando una prediccion sobre el valor de entrada del dato que recibe, dicha prediccion tendra mas porcentaje de acierto cuando la red haya sido entrenada usando forward pass en compañia de packward pass. De esta forma ....
	for l, layer in enumerate(neural_net):
		##print("Datos Entrada")
		##print(out[-1][1])
		##print("Pesos sinapticos capa")
		##print(l)
		##print(neural_net[l].W)
		##print("Bias capa")
		##print(neural_net[l].b)*/
		z = out[-1][1] @ neural_net[l].W + neural_net[l].b #z = Suma Ponderada + Parametro de Bies.
		a = neural_net[l].act_f[0](z)			   #a = Funcion de activacion para "entre otras cosas" evitar las linealidades. La realizamos sobre 'z' la suma ponderada producida anteriormente.
		out.append((z, a))				   #Guardamos los pares de informacion de suma ponderada y el resultado de su funcion de activacion.

	if train:

		#Backward Pass
		deltas = []

		for l in reversed(range(0, len(neural_net))): #Bucle hacia atras para realizar el "Backward Pass"

			z = out[l+1][0] #Se obtiene el valor de la suma ponderada guardado en el vector "out"
			a = out[l+1][1] #Se obtiene el valor de la funcion de activacion guardado en el vector "out"

			#If es true en la 1 iteracion.
			if l == len(neural_net) - 1: #Calcular delta de la ultima capa.
				deltas.insert(0, l2_cost[1](a, Y) * neural_net[l].act_f[1](a))
			else:			     #Calcular delta respecto a capa previa.
				deltas.insert(0, deltas[0] @ _W.T * neural_net[l].act_f[1](a))
			#Actualizamos el valor "Deltas dentro de la clase Neuronal_Network"
			#self.deltas.append(deltas)
			#"_W" se usa a partir de la 2 iteracion.
			_W = neural_net[l].W

			#Optimizacion de los valores con Descenso del Gradiente.
			neural_net[l].b = neural_net[l].b - np.mean(deltas[0], axis=0, keepdims=True) * lr #
			neural_net[l].W = neural_net[l].W - out[l][1].T @ deltas[0] * lr
	return out[-1][1]


################################################################################################################
##    Leyenda:                                                                                                ##
##                                        1 = 0cm(margen de error o menos). "Demasiado Cerca"                 ##
## 		                          0 = 25cm. "Obstaculo detectado" 		                      ##
##                                       -1 = 50cm o mas. "Sin obstaculos"                                    ##
## 		                                                                                              ##
################################################################################################################

## Posicion de los sensores de ultrasonidos.
##     Izquierda Centro Derecha
X = np.array([[-1, -1, -1], # Avanzar.                                       26
              [-1, -1,  1], # Atras.    -------                              25
              [-1, -1,  0], # Girar Izquierda.                               24
              [-1,  0,  0], # Girar Izquierda.                               23
              [-1,  0, -1], # Girar Izquierda.                               22
              [-1,  0,  1], # Atras             ---------------------------- 21
              [-1,  1, -1], # Atras             ---------------------------- 20
              [-1,  1,  0], # Atras  ---------                               19
              [-1,  1,  1], # Atras                           ---------------18
	      [ 0, -1, -1], # Girar Derecha -----------------                17
	      [ 0, -1, -1], # Girar Derecha -----------------                16
	      [ 0, -1,  1], # Atras      -----------                         15
	      [ 0,  0,  0], # Girar Izquierda.   ------------------------    14
	      [ 0,  0, -1], # Girar Derecha.                                 13
	      [ 0,  0,  1], # Atras.                                         12
	      [ 0,  1, -1], # Atras                           ---------------11
	      [ 0,  1,  0], # Atras.                                         10
	      [ 0,  1,  1], # Atras.                                          9
	      [ 1, -1, -1], # Atras                             ---------     8
	      [ 1, -1,  0], # Atras                          -------          7
	      [ 1, -1,  1], # Atras                           --------        6
	      [ 1,  0, -1], # Atras.   --------------                         5
	      [ 1,  0,  0], # Atras  ------------------------                 4
	      [ 1,  0,  1], # Atras.                                          3
	      [ 1,  1, -1], # Atras.---------                                 2
	      [ 1,  1,  0], # Atras.                                          1
	      [ 1,  1,  1], # Atras.                                          0
            ])

# las salidas 'y' se corresponden con encender (o no) los motores
y = np.array([[1,0,0,1,1,0,0,1], # Avanzar.                    26
	      [0,1,1,0,0,1,1,0], # Retroceder.   ----          25
	      [1,0,0,0,1,0,0,0], # Girar Izquierda.            24
	      [1,0,0,0,1,0,0,0], # Girar Izquierda.            23
	      [1,0,0,0,1,0,0,0], # Girar Izquierda.            22
	      [0,1,1,0,0,1,1,0], # Retroceder. ------          21
	      [0,1,1,0,0,1,1,0], # Retroceder. -------         20
	      [0,1,1,0,0,1,1,0], # Retroceder. -----           19
	      [0,1,1,0,0,1,1,0], # Retroceder.  ---            18
	      [0,0,0,1,0,0,0,1], # Girar Derecha. -------      17
	      [0,0,0,1,0,0,0,1], # Girar Derecha. -------      16
	      [0,1,1,0,0,1,1,0], # Retroceder.   ----          15
	      [1,0,0,0,1,0,0,0], # Girar Izquierda.  ------    14
	      [0,0,0,1,0,0,0,1], # Girar Derecha.              13
	      [0,1,1,0,0,1,1,0], # Retroceder.                 12
	      [0,1,1,0,0,1,1,0], # Retroceder.         -----   11
	      [0,1,1,0,0,1,1,0], # Retroceder.                 10
	      [0,1,1,0,0,1,1,0], # Retroceder.                  9
	      [0,1,1,0,0,1,1,0], # Retroceder. ---              8
	      [0,1,1,0,0,1,1,0], # Retroceder. ---              7
	      [0,1,1,0,0,1,1,0], # Retroceder. ---              6
	      [0,1,1,0,0,1,1,0], # Retroceder. ---              5
	      [0,1,1,0,0,1,1,0], # Retroceder. ---              4
	      [0,1,1,0,0,1,1,0], # Retroceder.                  3
	      [0,1,1,0,0,1,1,0], # Retroceder. --               2
	      [0,1,1,0,0,1,1,0], # Retroceder.                  1
	      [0,1,1,0,0,1,1,0], # Retroceder.                  0
	      ])


################################################################################################################
##                                 Creamos la red neuronal                                                    ##
################################################################################################################
p = 3 				       #Número de neuronas en la capa de entrada.
topology = [p, 6, 8] 	       #Topologia de la red que indica el numero de neuronas que pose cada capa.  #Aun no se que topologia usar#
##neural_net = create_nn(topology, tanh) #Creamos la estructura de la red y la recojemos en nueronal_net.
################################################################################################################
##                                 CODIGO PARA ENTRENAR NUESTRA RED NEURONAL                                  ##
################################################################################################################

import time
#from IPython.display import clear_output


def valNN(x):
    return (int)(abs(round(x)))

neural_n = np.copy(np.array(create_nn(topology, tanh)))

index=0

loss = []



for i in range(240001):
	#Entrenamos a la red neuronal
     pY = train(neural_n, X, y, l2_cost, lr=0.02)


pre = train(neural_n, X, y, l2_cost, lr=0.03, train=False)

#print(len(neural_n))
print(neural_n[0].W)
print(neural_n[0].b)
print(neural_n[1].W)
print(neural_n[1].b)

#for l in range (0, len(neural_n)):
#	print(neural_n[l])

def predic(y, pre):
	for l in range(0, len(pre)):
		print("deseado : ", y[l],"Predicho :",valNN(pre[l][0]),valNN(pre[l][1]),valNN(pre[l][2]),valNN(pre[l][3]),valNN(pre[l][4]),valNN(pre[l][5]),valNN(pre[l][6]),valNN(pre[l][7]))


predic(y, pre)





 
