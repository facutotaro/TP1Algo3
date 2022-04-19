Utilizando linux
Requisitos: Debemos tener instalado Cmake
Para compilar tenemos que hacer lo siguiente:
1) Nos ubicamos en el directorio en el cual tenemos descargado el archivo y abrimos una terminal
2) Lo descomprimimos usando el comando tar -xf archive.tar.gz
3) Luego accedemos al directorio tp1 con el comando cd src/tp1
4) Alli dentro ejecutamos la siguiente secuencia de comandos:
mkdir build
cd build 
cmake ..
make
5) Con eso ya tenemos el codigo compilado. Para ejecutarlo en la linea de comandos ejecutamos ./tp1 <ej> < <instancia> donde <ej> es el numero de ejercicio e instancia es el path relativo al archivo de entrada.
Se imprimirá en pantalla el resultado óptimo y el tiempo de ejecucion.
6) Si se quieren agregar archivos en los directorios de los ejercicios hay un directorio con el nombre instancias-i donde i es el numero de ejercicio
el cual tiene dentro una carpeta que se llama instancias. Las instancias que se quieran agregar deben estar dentro de ese directorio.
