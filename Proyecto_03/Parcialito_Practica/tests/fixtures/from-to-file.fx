# esperamos el menu
> .*

# hacemos dump de dict vacio bajo el nombre empty.dic
< u
# espero encontrar el prompt de ingresar nombre de archivo
> .*
# escribo el nombre de archivo
< empty.dic
# espero que me muestre un mensaje con "success" o "exitosamente"
> success|exitosamente

# agregamos: rojo
< a
> .*
< rojo
> .*
< De color parecido al del oro
> .*

# agregamos: azul
< a
> .*
< azul
> .*
< Del color del cielo sin nubes
> .*

# agregamos: amarillo
< a
> .*
< amarillo
> .*
< De color semejante al del oro, la flor de la retama
> .*

# mostramos el dict de colores primarios
< h
# esperamos encontrar
# {
# amarillo: De color semejante al del oro, la flor de la retama
# azul: Del color del cielo sin nubes
# rojo: De color parecido al del oro
# }
> {\s*amarillo: De color semejante al del oro, la flor de la retama\s*azul: Del color del cielo sin nubes\s*rojo: De color parecido al del oro\s*}

# hacemos dump de dict bajo el nombre primary.dic
< u
> .*
# escribo el nombre de archivo
< primary.dic
# espero que me muestre un mensaje con "success" o "exitosamente"
> success|exitosamente

# agregamos: verde
< a
> .*
< verde
> .*
< De color semejante al de la hierba fresca, la esmeralda
> .*

# pido el tamaño
< z
# espero encontrar 4
> [4]

# cargo el primary.dic pisando el dict con 4 elementos
< l
> .*
# ingreso el archivo primary.dic
< primary.dic
# espero que me muestre un mensaje con "success" o "exitosamente"
> success|exitosamente

# pido el tamaño
< z
# espero encontrar 3
> [3]

# borro azul
< d
> .*
< azul
# espero que me muestre un mensaje con "success" o "exitosamente"
> success|exitosamente

# pido el tamaño
< z
# espero encontrar 2
> [2]

# mostramos el dict de colores primarios sin el azul
< h
# esperamos encontrar
# {
# amarillo: De color semejante al del oro, la flor de la retama
# rojo: De color parecido al del oro
# }
> {\s*amarillo: De color semejante al del oro, la flor de la retama\s*rojo: De color parecido al del oro\s*}

# cargo
# salir chequeando leaks
< q
> All heap blocks were freed -- no leaks are possible
