-- CONSTRUCTORES
data Pila e = Vacía
            | Apilar e (Pila e)
            deriving (Eq, Show)


-- OPERACIONES
es_vacía :: Pila e -> Bool
primero :: Pila e -> e        -- se aplica solo a una pila no Vacía
desapilar :: Pila e -> Pila e -- se aplica solo a una pila no Vacía


-- ECUACIONES
es_vacía Vacía = True
es_vacía (Apilar e p) = False

primero Vacía = error "No se puede obtener el primero de la pila Vacía"
primero (Apilar e p) = e

desapilar Vacía = error "No se puede desapilar la pila Vacía"
desapilar (Apilar e p) = p


-- EJEMPLOS
primera = Vacía
segunda = Apilar 2 primera
tercera = Apilar 5 segunda

todos = Vacía : concatMap (\p -> [Apilar ']' p, Apilar '}' p]) todos

cierto = segunda == desapilar tercera


-- DELIMITADORES BALANCEADOS
balanceados = ctrl_balanceo Vacía

ctrl_balanceo p [] = es_vacía p
ctrl_balanceo p (l:s) | izq l = ctrl_balanceo (Apilar (cierre l) p) s
                      | der l && es_vacía p = False
                      | der l && l /= primero p = False
                      | der l && l == primero p = ctrl_balanceo (desapilar p) s
                      | otherwise = ctrl_balanceo p s


izq l = l `elem` ['(','[','{','<']

der l = l `elem` [')',']','}','>']

cierre '(' = ')'
cierre '[' = ']'
cierre '{' = '}'
cierre '<' = '>'
