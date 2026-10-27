import random
import argparse

def gerar_entradas(args):
    random.seed(args.semente)
    
    metricas_validas = ['PODER', 'EQUILIBRIO', 'SINERGIA']
    
    with open(args.saida, 'w') as f:
        f.write(f"E {args.modo}\n")
        
        for i in range(args.T):
            f.write(f"A Atributo_{i}\n")
        for i in range(args.N):
            f.write(f"I Item_{i}\n")
        for i in range(args.V):
            f.write(f"H Aventureiro_{i}\n")
            
        total_celulas = args.N * args.T
        celulas_iniciais = int(total_celulas * args.densidade)
        celulas_geradas = set()
        
        while len(celulas_geradas) < celulas_iniciais:
            item_id = random.randint(0, args.N - 1)
            attr_id = random.randint(0, args.T - 1)
            celulas_geradas.add((item_id, attr_id))
            
        for item_id, attr_id in celulas_geradas:
            valor = random.choice([v for v in range(-15, 16) if v != 0])
            f.write(f"M {item_id} {attr_id} {valor}\n")
            
        encomendas_totais = 0
        for av_id in range(args.V):
            tamanho_build = max(1, int(random.gauss(args.build_media, 2)))
            itens_build = random.choices(range(args.N), k=tamanho_build)
            for item_id in itens_build:
                f.write(f"F {av_id} {item_id}\n")
                encomendas_totais += 1
        
        if encomendas_totais > 0:
            f.write(f"Z {encomendas_totais}\n")
            
        # Definição dos pesos com base na proporção solicitada
        p_upd = args.perc_atualizacao
        p_qry = 1.0 - p_upd
        
        # Distribuição interna (pode ajustar essas frações se quiser dar mais peso a um comando específico)
        # Atualizações: M (40%), F (30%), Z (20%), D (10%)
        # Consultas: Q (35%), LH (35%), LF (10%), LI (10%), LA (10%)
        comandos = ['M', 'F', 'Z', 'D', 'Q', 'LH', 'LF', 'LI', 'LA']
        pesos = [
            #0.20 * p_upd, 0.35 * p_upd, 0.35 * p_upd, 0.10 * p_upd,
            #0.40 * p_upd, 0.30 * p_upd, 0.20 * p_upd, 0.10 * p_upd,
            0.40 * p_upd, 0.30 * p_upd, 0.30 * p_upd, 0.0 * p_upd,
            0.35 * p_qry, 0.35 * p_qry, 0.10 * p_qry, 0.10 * p_qry, 0.10 * p_qry
        ]
        
        for _ in range(args.operacoes):
            cmd = random.choices(comandos, weights=pesos)[0]
            
            if cmd == 'M':
                item_id = random.randint(0, args.N - 1)
                attr_id = random.randint(0, args.T - 1)
                valor = random.randint(-10, 10) 
                f.write(f"M {item_id} {attr_id} {valor}\n")
                
            elif cmd == 'F':
                av_id = random.randint(0, args.V - 1)
                item_id = random.randint(0, args.N - 1)
                f.write(f"F {av_id} {item_id}\n")
                
            elif cmd == 'Z':
                k = random.randint(1, 5) 
                f.write(f"Z {k}\n")
                
            elif cmd == 'D':
                av_id = random.randint(0, args.V - 1)
                f.write(f"D {av_id}\n")
                
            elif cmd == 'Q':
                av_id = random.randint(0, args.V - 1)
                n_retorno = random.randint(1, 10)
                m_metrics = random.randint(1, 3)
                metricas = random.sample(metricas_validas, m_metrics)
                
                linha_q = f"Q {av_id} {n_retorno} {m_metrics}"
                for metrica in metricas:
                    peso = random.uniform(1.0, 5.0)
                    linha_q += f" {metrica} {peso:.2f}"
                f.write(linha_q + "\n")
                
            elif cmd == 'LH':
                av_id = random.randint(0, args.V - 1)
                f.write(f"LH {av_id}\n")
                
            elif cmd == 'LF':
                attr_id = random.randint(0, args.T - 1)
                val_min = random.randint(-15, 15)
                val_max = random.randint(val_min, 30)
                f.write(f"LF {attr_id} {val_min} {val_max}\n")
                
            elif cmd == 'LI':
                item_id = random.randint(0, args.N - 1)
                f.write(f"LI {item_id}\n")
                
            elif cmd == 'LA':
                attr_id = random.randint(0, args.T - 1)
                f.write(f"LA {attr_id}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Gerador de Entradas exatas para TP1 - A Forja do Blibblon")
    parser.add_argument('--modo', type=str, choices=['L', 'T', 'C'], default='L', help='Modo inicial (L ou T)')
    parser.add_argument('--N', type=int, default=500, help='Número de itens')
    parser.add_argument('--T', type=int, default=500, help='Número de atributos')
    parser.add_argument('--V', type=int, default=100, help='Número de aventureiros')
    parser.add_argument('--densidade', type=float, default=0.15, help='Densidade (0.0 a 1.0)')
    parser.add_argument('--build_media', type=int, default=15, help='Tamanho médio da build')
    parser.add_argument('--operacoes', type=int, default=1000, help='Quantidade de transações')
    parser.add_argument('--perc_atualizacao', type=float, default=0.75, help='Proporção de operações de atualização (M, F, Z, D) entre 0.0 e 1.0')
    parser.add_argument('--semente', type=int, default=13, help='Semente de aleatoriedade')
    parser.add_argument('--saida', type=str, default='teste_exp.txt', help='Arquivo de saída')
    
    args = parser.parse_args()
    gerar_entradas(args)
    print(f"Arquivo '{args.saida}' gerado com sucesso.")
    print(f"Carga: {args.perc_atualizacao*100:.0f}% Atualizações / {(1.0-args.perc_atualizacao)*100:.0f}% Consultas.")