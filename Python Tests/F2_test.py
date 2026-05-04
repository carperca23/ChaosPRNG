import numpy as np
import matplotlib.pyplot as plt

# Definición de la función F2 según el documento "07.pdf"
def F2(y):
    return 4 * y**3 - 3 * y

def plot_f2_chaos():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    fig.suptitle('Análisis de Caos: Función F2(y) = 4y³ - 3y', fontsize=16)

    # ==========================================
    # 1. Sensibilidad a las condiciones iniciales
    # ==========================================
    iterations = 40
    y1_val = -0.4
    y2_val = -0.400001
    
    seq1 = [y1_val]
    seq2 = [y2_val]
    
    for _ in range(iterations):
        seq1.append(F2(seq1[-1]))
        seq2.append(F2(seq2[-1]))
        
    ax1.plot(seq1, label='Inicial = -0.4', color='green', marker='o', markersize=4, linewidth=1)
    ax1.plot(seq2, label='Inicial = -0.400001', color='purple', marker='x', markersize=4, linewidth=1, linestyle='dashed')
    ax1.set_title('Sensibilidad (Efecto Mariposa)')
    ax1.set_xlabel('Iteración (N)')
    ax1.set_ylabel('Valor (Y)')
    ax1.legend()
    ax1.grid(True, linestyle='--', alpha=0.7)

    # ==========================================
    # 2. Diagrama de Cobweb (Telaraña)
    # ==========================================
    y_vals_in = np.linspace(-1, 1, 500)
    y_vals_out = F2(y_vals_in)
    
    ax2.plot(y_vals_in, y_vals_out, label='F2(y)', color='green')
    ax2.plot(y_vals_in, y_vals_in, label='y = x (Diagonal)', color='gray', linestyle='--')
    
    # Generar la telaraña
    y_cobweb = 0.789
    for _ in range(50):
        next_y = F2(y_cobweb)
        ax2.plot([y_cobweb, y_cobweb], [y_cobweb, next_y], color='purple', alpha=0.6, linewidth=1)
        ax2.plot([y_cobweb, next_y], [next_y, next_y], color='purple', alpha=0.6, linewidth=1)
        y_cobweb = next_y
        
    ax2.set_title('Diagrama de Red')
    ax2.set_xlabel('y(n)')
    ax2.set_ylabel('y(n+1)')
    ax2.legend()
    ax2.grid(True, linestyle='--', alpha=0.7)
    ax2.set_xlim([-1.05, 1.05])
    ax2.set_ylim([-1.05, 1.05])

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    plot_f2_chaos()