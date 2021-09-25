# Pasos para instalar (EIGEN)[https://eigen.tuxfamily.org/dox/GettingStarted.html]


```bash
FISIDIR="<coloque la ruta al directorio de FISI2028-202120>"
mkdir ~/LIBS
cd ~/LIBS
git clone https://gitlab.com/libeigen/eigen.git
cd $FISIDIR/ejercicios/semana5
echo "Ahora para compilar..."
g++ -std=c++14 -Wall -Werror -pedantic -I ~/LIBS/eigen matrix1.cpp -o exe
```

No olviden actualizar sus repositorios propios para la tarea y después hacer el "Pull Request"
