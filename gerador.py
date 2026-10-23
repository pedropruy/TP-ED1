import random

# A semente 42 garante que os valores "aleatórios" serão SEMPRE os mesmos.
# Isso é crucial: se o seu C++ falhar na linha 412 hoje, falhará na mesma linha amanhã.
random.seed(42)

with open("estresse.txt", "w") as f:
    f.write("E T\n") # 1. Inicia no Modo COO
    
    # Cadastros Base (100 Atributos, 100 Itens, 20 Heróis)
    for i in range(100): f.write(f"A Atributo_{i}\n")
    for i in range(100): f.write(f"I Item_{i}\n")
    for i in range(20):  f.write(f"H Heroi_{i}\n")
    
    # 2. Modificadores (600 valores, misturando status altamente negativos)
    for _ in range(600):
        id_i = random.randint(0, 99)
        id_a = random.randint(0, 99)
        valor = random.randint(-50, 50)
        if valor == 0: valor = 1
        f.write(f"M {id_i} {id_a} {valor}\n")
        
    # 3. Filas Extensas (Estressa o dobramento de capacidade da sua Fila)
    for _ in range(150):
        id_h = random.randint(0, 19)
        id_i = random.randint(0, 99)
        f.write(f"F {id_h} {id_i}\n")
        
    f.write("Z 100\n") # Atende 100 pedidos de uma vez só
    
    # 4. Troca de Contextos (Modo T -> Modo L com memória suja)
    f.write("E L\n") 
    
    # 5. Queries Complexas com itens equipados e modos alterados
    f.write("LH 5\n")
    f.write("LF 10 -30 30\n")
    f.write("Q 5 15 3 PODER 1.0 EQUILIBRIO 1.5 SINERGIA 2.0\n")
    
    # 6. Atualizações pós-troca (Força inserção na matriz encadeada)
    f.write("M 0 0 100\n")
    f.write("M 0 1 -100\n")
    
    # 7. Desequipar em massa (Testa vazamento de memória da build)
    for i in range(20):
        f.write(f"D {i}\n")
        
    # 8. Retorno de Contexto (Modo L -> Modo T)
    f.write("E T\n")
    f.write("F 0 0\n")
    f.write("Z 1\n")
    f.write("Q 0 5 1 PODER 1.0\n")

print("Arquivo 'estresse.txt' gerado com sucesso!")