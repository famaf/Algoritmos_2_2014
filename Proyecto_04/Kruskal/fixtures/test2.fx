# cargamos grafo
< # 7 10
< graph G {
<   1 -- 2 [label=0];
<   1 -- 3 [label=1];
<   3 -- 4 [label=2];
<   3 -- 2 [label=3];
<   5 -- 6 [label=4];
<   5 -- 4 [label=5];
<   6 -- 4 [label=6];
<   7 -- 4 [label=7];
<   7 -- 5 [label=8];
<   7 -- 6 [label=10];
< }

# chequeamos aristas de salida
> # 7 10
> 7 -- 4 \[label=7\];
> 5 -- 4 \[label=5\];
> 5 -- 6 \[label=4\];
> 3 -- 4 \[label=2\];
> 1 -- 3 \[label=1\];
> 1 -- 2 \[label=0\];
> 6 -- 4 \[label=6,style=dotted\];
> 3 -- 2 \[label=3,style=dotted\];
> 7 -- 5 \[label=8,style=dotted\];
> 7 -- 6 \[label=10,style=dotted\];

# chequeamos leaks
> All heap blocks were freed -- no leaks are possible
: Hay leaks!
