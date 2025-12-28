;; Testes de Lógica e Comparação
(= 10 10)             ; T (#t ou o teu objeto true)
(< 5 10 15)           ; T
(> 20 10 5)           ; T
(<= 10 10 11)         ; T
(not (= 1 2))         ; T
(cond ((= 1 2) 10) 
      ((= 1 1) 20) 
      (1 30))         ; Deve retornar 20