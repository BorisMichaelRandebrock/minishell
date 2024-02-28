#!/bin/bash

# Verificar si se han pasado al menos un argumento
if [ $# -eq 0 ]; then
    echo "No se ha pasado ningún argumento."
    exit 1
fi

# Mostrar el número de argumentos
echo "El número de argumentos pasados es: $#"
