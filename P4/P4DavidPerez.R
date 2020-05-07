# Autor: David Perez Nunez

# ---------------------------------------------------------------------------

# Antes de hacer los ejercicios necesitamos instalar los siguientes paquetes ...

install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)
install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
library(soundgen)
library(audio)

# ... y establecer el path concreto en cada caso a la carpeta de trabajo
setwd("D:\\Users\\david\\Documents\\Cosas_David\\Universidad\\Facultad\\Cuarto\\2Cuatrimestre\\PDIH\\DOSBOX\\P4")
# la siguiente linea, solo para macOS
# setWavPlayer('/usr/bin/afplay')

# ---------------------------------------------------------------------------

# Ejercicio 1: Leer dos ficheros de sonido (WAV o MP3) de unos pocos segundos de 
# duración cada uno.

perro <- readWave('perro.wav')
perro
gato  <- readMP3('gato.mp3')
gato

# Ejercicio 2: Dibujar la forma de onda de ambos sonidos.

plot( extractWave(perro, from = 1, to = 159732) )
plot( extractWave(gato, from = 1, to = 393984) )

# Ejercicio 3: Obtener la información de las cabeceras de ambos sonidos.

# Cuando ejecutas el ejercicio 1 te aparecen unos datos en la consola. Esos
# datos son las cabeceras de los archivos leidos

# Ejercicio 4: Unir ambos sonidos en uno nuevo.

gatoperro <- pastew(gato, perro, output="Wave")
gatoperro
round(length(gatoperro@left) / gato@samp.rate, 3)
f <- gatoperro@samp.rate
listen(gatoperro,f=f)

# Ejercicio 5: Dibujar la forma de onda de la señal resultante.

plot( extractWave(gatoperro, from = 1, to = 553716) )

# Ejercicio 6: Pasarle un filtro de frecuencia para eliminar las frecuencias
# por debajo de 3.000Hz

gatoperrofil <- afilter(gatoperro,f=3000,output = "Wave")
listen(gatoperrofil,f=f)

# Ejercicio 7: Almacenar la señal obtenida como un fichero WAV denominado 
# "mezcla.wav"

writeWave(gatoperrofil, file.path("mezcla.wav") )

# Ejercicio 8: Cargar un nuevo archivo de sonido, aplicarle eco y a continuación
# darle la vuelta al sonido. Almacenar la señal obtenida como un fichero WAV
# denominado "alreves.wav".

oveja <- readWave('oveja.wav')
f <- oveja@samp.rate    #22050
str(oveja)
ovejaECO <- echo(oveja,f=f,amp=c(0.8,0.4,0.2),delay=c(1,2,3),output="Wave")
ovejaECO@left <- 10000*ovejaECO@left
listen(ovejaECO,f=f)
str(ovejaECO)
plot(extractWave(ovejaECO,from=1,to=77959))
ovejaECOalreves <- revw(ovejaECO, output="Wave")
listen(ovejaECOalreves)
plot(extractWave(ovejaECOalreves,from=1,to=77959))
writeWave(ovejaECOalreves, file.path("alreves.wav") )


