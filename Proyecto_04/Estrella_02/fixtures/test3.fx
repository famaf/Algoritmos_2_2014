# cargamos grafo
< # 5 4
< graph G {
<  1 -- 2 [label=15];
<  1 -- 3 [label=18];
<  2 -- 4 [label=12];
<  3 -- 5 [label=8];
< }


# chequeamos aristas de salida
> # 5 4
> 1 -- 3 \[label=18\];
> 1 -- 2 \[label=15\];
> 2 -- 4 \[label=12\];
> 3 -- 5 \[label=8\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!
