# cargamos grafo
< # 7 10
< graph G {
< 1 -- 2 [label=45];
< 1 -- 3 [label=3];
< 3 -- 4 [label=8];
< 3 -- 2 [label=20];
< 5 -- 6 [label=13];
< 5 -- 4 [label=1];
< 6 -- 4 [label=32];
< 7 -- 4 [label=33];
< 7 -- 5 [label=3];
< 7 -- 6 [label=25];
< }

# chequeamos aristas de salida
> # 7 10
> 3 -- 2 \[label=20\];
> 5 -- 6 \[label=13\];
> 3 -- 4 \[label=8\];
> 7 -- 5 \[label=3\];
> 1 -- 3 \[label=3\];
> 5 -- 4 \[label=1\];
> 7 -- 6 \[label=25,style=dotted\];
> 6 -- 4 \[label=32,style=dotted\];
> 7 -- 4 \[label=33,style=dotted\];
> 1 -- 2 \[label=45,style=dotted\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!