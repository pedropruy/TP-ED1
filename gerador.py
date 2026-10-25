import random
import argparse

def gerar_entradas(args):
    random.seed(args.semente)
    
    # As três métricas obrigatórias da especificação
    metricas_validas = ['PODER', 'EQUILIBRIO', 'SINERGIA']
    
    with open(args.saida, 'w') as f:
        # 1. Definição do modo (Primeira linha obrigatória)
        f.write(f"E {args.modo}\n")
        
        # 2. Cadastro inicial (IDs automáticos de 0 a N-1 / T-1 / V-1)
        for i in range(args.T):
            f.write(f"A Atributo_{i}\n")
        for i in range(args.N):
            f.write(f"I Item_{i}\n")
        for i in range(args.V):
            f.write(f"H Aventureiro_{i}\n")
            
        # 3. Inserção Inicial na Matriz (Densidade)
        # O valor do modificador deve ser inteiro
        total_celulas = args.N * args.T
        celulas_iniciais = int(total_celulas * args.densidade)
        celulas_geradas = set()
        
        while len(celulas_geradas) < celulas_iniciais:
            item_id = random.randint(0, args.N - 1)
            attr_id = random.randint(0, args.T - 1)
            celulas_geradas.add((item_id, attr_id))
            
        for item_id, attr_id in celulas_geradas:
            # Sorteia valores inteiros e exclui o 0 nesta etapa para garantir a densidade real
            valor = random.choice([v for v in range(-15, 16) if v != 0])
            f.write(f"M {item_id} {attr_id} {valor}\n")
            
        # 4. Geração das Builds Iniciais
        # Encomenda os itens para os aventureiros (F) e os forja imediatamente (Z)
        encomendas_totais = 0
        for av_id in range(args.V):
            tamanho_build = max(1, int(random.gauss(args.build_media, 2)))
            # Um aventureiro pode equipar o mesmo item mais de uma vez
            itens_build = random.choices(range(args.N), k=tamanho_build)
            for item_id in itens_build:
                f.write(f"F {av_id} {item_id}\n")
                encomendas_totais += 1
        
        if encomendas_totais > 0:
            f.write(f"Z {encomendas_totais}\n")
            
        # 5. Fase de Operações (Simulação do perfil de carga)
        # Comandos disponíveis e seus pesos de probabilidade de ocorrência
        comandos = ['M', 'F', 'Z', 'D', 'LI', 'LA', 'LH', 'Q', 'LF']
        pesos = [0.20, 0.15, 0.15, 0.05, 0.05, 0.05, 0.15, 0.10, 0.10]
        
        for _ in range(args.operacoes):
            cmd = random.choices(comandos, weights=pesos)[0]
            
            if cmd == 'M':
                item_id = random.randint(0, args.N - 1)
                attr_id = random.randint(0, args.T - 1)
                # Permite 0 para testar a remoção lógica de células
                valor = random.randint(-10, 10) 
                f.write(f"M {item_id} {attr_id} {valor}\n")
                
            elif cmd == 'F':
                av_id = random.randint(0, args.V - 1)
                item_id = random.randint(0, args.N - 1)
                f.write(f"F {av_id} {item_id}\n")
                
            elif cmd == 'Z':
                # k deve ser estritamente positivo
                k = random.randint(1, 5) 
                f.write(f"Z {k}\n")
                
            elif cmd == 'D':
                av_id = random.randint(0, args.V - 1)
                f.write(f"D {av_id}\n")
                
            elif cmd == 'LI':
                item_id = random.randint(0, args.N - 1)
                f.write(f"LI {item_id}\n")
                
            elif cmd == 'LA':
                attr_id = random.randint(0, args.T - 1)
                f.write(f"LA {attr_id}\n")
                
            elif cmd == 'LH':
                av_id = random.randint(0, args.V - 1)
                f.write(f"LH {av_id}\n")
                
            elif cmd == 'Q':
                av_id = random.randint(0, args.V - 1)
                n_retorno = random.randint(1, 10)
                m_metrics = random.randint(1, 3)
                metricas = random.sample(metricas_validas, m_metrics)
                
                linha_q = f"Q {av_id} {n_retorno} {m_metrics}"
                for metrica in metricas:
                    # Pesos gerados como float estrito e impressos com 2 casas decimais
                    peso = random.uniform(1.0, 5.0)
                    linha_q += f" {metrica} {peso:.2f}"
                f.write(linha_q + "\n")
                
            elif cmd == 'LF':
                attr_id = random.randint(0, args.T - 1)
                val_min = random.randint(-15, 15)
                val_max = random.randint(val_min, 30)
                f.write(f"LF {attr_id} {val_min} {val_max}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Gerador de Entradas exatas para TP1 - A Forja do Blibblon")
    parser.add_argument('--modo', type=str, choices=['L', 'T', 'C'], default='L', help='Modo inicial (L ou T)')
    parser.add_argument('--N', type=int, default=1000, help='Número de itens')
    parser.add_argument('--T', type=int, default=50, help='Número de atributos')
    parser.add_argument('--V', type=int, default=100, help='Número de aventureiros')
    parser.add_argument('--densidade', type=float, default=0.05, help='Densidade (0.0 a 1.0)')
    parser.add_argument('--build_media', type=int, default=10, help='Tamanho médio da build')
    parser.add_argument('--operacoes', type=int, default=1000, help='Quantidade de transações')
    parser.add_argument('--semente', type=int, default=42, help='Semente de aleatoriedade')
    parser.add_argument('--saida', type=str, default='teste_exp.txt', help='Arquivo de saída')
    
    args = parser.parse_args()
    gerar_entradas(args)
    print(f"Arquivo '{args.saida}' gerado com sucesso (Modo: {args.modo}, Semente: {args.semente}).")