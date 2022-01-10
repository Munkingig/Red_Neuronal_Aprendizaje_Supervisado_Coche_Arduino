# Red_Neuronal_Coche_Arduino
Red neuronal de aprendizaje supervisado, entrenada para controlar un robot en forma de coche, implementada mediante Python, sin uso de librerías como Tensorflow, Keras, Pytorch, etc. Se solventan limitaciones Hardware por parte del robot, mediante técnica de inferencia.

El primer archivo se implementa la red neuronal en Python para ser entrenada en la tarea deseada.
En el segundo archivo se implementa lo necersario para que el roboit en forma de coche pueda utilizar sus sensores y solventar la limitacion hardware ofrecida por el microcontrolador arduino a la hora de ejecutar una red neuronal mediante el uso de una pequeña técnica de inferencia. Donde se traslada el aprendizaje realizado por la red neuronal en Python. De esta forma Arduino solo tiene que ejecutar la parte predictiva de una red neuronal y no realizar el aprendizaje, evitando asi las limitaciones de harware de las que dispone Arduino.

Video del resultado robot terminado: https://www.youtube.com/watch?v=9B5d0pQ-ayM

