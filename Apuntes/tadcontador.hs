-- CONSTRUCTORES
data Contador = Inicial
              | Incrementar Contador
              deriving (Eq, Show)


-- OPERACIONES
es_inicial :: Contador -> Bool
decrementar :: Contador -> Contador -- se aplica solo a un contador que no sea Inicial


-- ECUACIONES
es_inicial Inicial = True
es_inicial (Incrementar c) = False

decrementar Inicial = error "No se puede decrementar el contador Inicial"
decrementar (Incrementar c) = c


-- EJEMPLOS
primero = Inicial
segundo = Incrementar primero
tercero = Incrementar segundo

todos = Inicial : map Incrementar todos

cierto = segundo == decrementar tercero


-- PARÉNTESIS BALANCEADOS
balanceados :: String -> Bool
balanceados = ctrl_balanceo Inicial

ctrl_balanceo :: Contador -> String -> Bool
ctrl_balanceo c [] = es_inicial c
ctrl_balanceo c (l:s) | l == '(' = ctrl_balanceo (Incrementar c) s
                      | l == ')' && es_inicial c = False
                      | l == ')' = ctrl_balanceo (decrementar c) s
                      | otherwise = ctrl_balanceo c s
