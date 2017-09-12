# cargamos grafo
< # 7 7
< graph G {
<   1 -- 2 [label=7];
<   1 -- 4 [label=5];
<   2 -- 3 [label=8];
<   2 -- 4 [label=9];
<   5 -- 6 [label=8];
<   5 -- 7 [label=9];
<   6 -- 7 [label=11];
< }


# chequeamos aristas de salida
> # 7 7
> 5 -- 7 \[label=9\];
> 5 -- 6 \[label=8\];
> 2 -- 3 \[label=8\];
> 1 -- 2 \[label=7\];
> 1 -- 4 \[label=5\];
> 6 -- 7 \[label=11,style=dotted\];
> 2 -- 4 \[label=9,style=dotted\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!
