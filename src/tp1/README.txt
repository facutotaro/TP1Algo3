Utilizando linux
Requisitos: Debemos tener instalado Cmake
Para compilar tenemos que hacer lo siguiente:
1) Nos ubicamos en el directorio en el cual tenemos descargado el archivo y abrimos una terminal
2) Lo descomprimimos usando el comando tar -xf TP1Algo3.tar.gz
3) Luego accedemos al directorio tp1 con el comando cd src/tp1
4) Alli dentro ejecutamos la siguiente secuencia de comandos:
mkdir build
cd build 
cmake ..
make

5) Para correr varias instancias que se encuentren en un directorio podemos hacer lo siguiente
echo "instancias" > <archivo de salida>
echo "" >> <archivo de salida>
for i in <ruta>/*
do
	base_name=$(basename $i)
	echo ${base_name} >> <archivo de salida>
	echo $i > name.txt
	/usr/bin/time -f "Tardó: %e" -o <archivo de salida> -a timeout 800 ./tp1 <ej> < name.txt >> res2.output
	echo "" >> <archivo de salida>
done

donde <ruta> es ruta relativa a la carpeta build, <archivo de salida> es el nombre del archivo donde queremos ejecutar los resultados y <ej> es el numero de ejecicio

5bis) Si queremos ejecutar un solo archivo podemos ejecutar ./tp1 <ej> y pulsamos "Enter" y luego escribimos el nombre del archivo incluyendo a su ruta relativa a la carpeta build.


