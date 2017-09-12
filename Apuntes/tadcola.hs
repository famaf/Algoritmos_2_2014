-- CONSTRUCTORES
data Cola e = Vacía
            | Encolar (Cola e) e
            deriving (Eq, Show)


-- OPERACIONES
es_vacía :: Cola e -> Bool
primero :: Cola e -> e        -- se aplica solo a una cola no Vacía
decolar :: Cola e -> Cola e   -- se aplica solo a una cola no Vacía


-- ECUACIONES
es_vacía Vacía = True
es_vacía (Encolar q e) = False

primero Vacía = error "No se puede obtener el primero de la cola Vacía"
primero (Encolar q e) | es_vacía q = e
                      | otherwise = primero q

decolar Vacía = error "No se puede decolar la cola Vacía"
decolar (Encolar q e) | es_vacía q = q
                      | otherwise = Encolar (decolar q) e

-- EJEMPLOS
primera = Vacía
segunda = Encolar primera 2
tercera = Encolar segunda 5

todos = Vacía : concatMap (\q -> [Encolar q ']', Encolar q '}']) todos

cierto = segunda == decolar tercera
