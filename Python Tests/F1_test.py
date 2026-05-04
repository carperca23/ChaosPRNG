import numpy as np
import matplotlib.pyplot as plt

def F1(x):
    return 2 * x**2 - 1

def plot_f1_chaos():
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    fig.suptitle('Análisis de Caos: Función F1(x) = 2x² - 1', fontsize=16)

    # ==========================================
    # 1. Sensibilidad a las condiciones iniciales
    # ==========================================
    iterations = 60
    x1_val = 0.6
    x2_val = 0.600001
    
    seq1 = [x1_val]
    seq2 = [x2_val]
    
    for _ in range(iterations):
        seq1.append(F1(seq1[-1]))
        seq2.append(F1(seq2[-1]))
        
    ax1.plot(seq1, label='Inicial = 0.6', color='blue', marker='o', markersize=4, linewidth=1)
    ax1.plot(seq2, label='Inicial = 0.600001', color='red', marker='x', markersize=4, linewidth=1, linestyle='dashed')
    ax1.set_title('Sensibilidad (Efecto Mariposa)')
    ax1.set_xlabel('Iteración (N)')
    ax1.set_ylabel('Valor (X)')
    ax1.legend()
    ax1.grid(True, linestyle='--', alpha=0.7)

    # ==========================================
    # 2. Diagrama de Cobweb (Telaraña)
    # ==========================================
    x_vals = np.linspace(-1, 1, 500)
    y_vals = F1(x_vals)
    
    ax2.plot(x_vals, y_vals, label='F1(x)', color='blue')
    ax2.plot(x_vals, x_vals, label='y = x', color='gray', linestyle='--')
    
    # Generar la telaraña
    x_cobweb = 0.234 # Punto de inicio arbitrario
    for _ in range(50):
        y_cobweb = F1(x_cobweb)
        ax2.plot([x_cobweb, x_cobweb], [x_cobweb, y_cobweb], color='red', alpha=0.6, linewidth=1)
        ax2.plot([x_cobweb, y_cobweb], [y_cobweb, y_cobweb], color='red', alpha=0.6, linewidth=1)
        x_cobweb = y_cobweb
        
    ax2.set_title('Diagrama de Red')
    ax2.set_xlabel('x(n)')
    ax2.set_ylabel('x(n+1)')
    ax2.legend()
    ax2.grid(True, linestyle='--', alpha=0.7)
    ax2.set_xlim([-1.05, 1.05])
    ax2.set_ylim([-1.05, 1.05])

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    plot_f1_chaos()