;; Fibonacci Recursivo
(define fib (lambda (n) 
  (cond ((= n 0) 0) 
        ((= n 1) 1) 
        (1 (+ (fib (- n 1)) (fib (- n 2)))))))

(print (fib 10))              ; Deve retornar 55