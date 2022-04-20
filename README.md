# Instrucciones para compilación
Utilizando Linux
Requisitos: Debemos tener instalado Cmake

Para instalarlo debemos ejecutar el comando:
sudo apt-get install cmake

Para compilar tenemos que hacer lo siguiente:
1) Luego accedemos al directorio tp1 con el comando cd src/tp1
2) Alli dentro ejecutamos la siguiente secuencia de comandos:
mkdir build
cd build 
cmake ..
make

3) Para correr varias instancias que se encuentren en un directorio podemos hacer lo siguiente
echo "instancias" > <archivo de salida>
echo "" >> <archivo de salida>
for i in <ruta>/*
do
	base_name=$(basename $i)
	echo ${base_name} >> <archivo de salida>
	echo $i > name.txt
	/usr/bin/time -f "Tardó: %e" -o <archivo de salida> -a timeout 800 ./tp1 <ej> < name.txt >>  <archivo de salida>
	echo "" >> <archivo de salida>
done

donde <ruta> es ruta relativa a la carpeta build, <archivo de salida> es el nombre del archivo donde queremos ejecutar los resultados y <ej> es el numero de ejecicio

3bis) Si queremos ejecutar un solo archivo podemos ejecutar ./tp1 <ej> y pulsamos "Enter" y luego escribimos el nombre del archivo incluyendo a su ruta relativa a la carpeta build.
