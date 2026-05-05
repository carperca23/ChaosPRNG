import numpy as np
import matplotlib.pyplot as plt
import os

def analizar_binario_completo(filename, ancho_bitmap=256):
    """
    Lee TODO el contenido de un archivo binario y genera:
    1. Mapa de bits visual.
    2. Gráfico de frecuencias de bits (0 vs 1).
    """
    if not os.path.exists(filename):
        print(f"Error: No se encontró el archivo '{filename}'. Comprueba el nombre y la ruta.")
        return

    print(f"Leyendo el archivo completo '{filename}'...")
    with open(filename, 'rb') as f:
        byte_data = f.read()
        
    tamano_mb = len(byte_data) / (1024 * 1024)
    print(f"Archivo cargado con éxito: {len(byte_data):,} bytes ({tamano_mb:.2f} MB)")
    
    byte_array = np.frombuffer(byte_data, dtype=np.uint8)
    print("Desempaquetando bits y procesando matrices...")
    bit_array = np.unpackbits(byte_array)
    
    filas = len(bit_array) // ancho_bitmap
    bits_recortados = bit_array[:filas * ancho_bitmap]
    matriz_bits = bits_recortados.reshape((filas, ancho_bitmap))
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    fig.suptitle('Análisis Estadístico del PRNG: Bits', fontsize=16)
    
    ax1.imshow(matriz_bits, cmap='binary', aspect='auto', interpolation='nearest')
    ax1.set_title(f'Mapa de Bits ({ancho_bitmap} bits de ancho)')
    ax1.set_xlabel('Columnas (Bits)')
    ax1.set_ylabel('Filas')
    
    total_bits = len(bit_array)
    unos = np.sum(bit_array)
    ceros = total_bits - unos
    
    barras = ax2.bar(['Bit 0', 'Bit 1'], [ceros, unos], color=['#e63946', '#457b9d'], edgecolor='black', zorder=3)
    ax2.set_title('Frecuencia de Ceros y Unos')
    ax2.set_ylabel('Cantidad total')
    
    frecuencia_ideal = total_bits / 2
    ax2.axhline(y=frecuencia_ideal, color='black', linestyle='--', linewidth=2, label=f'Ideal 50% ({frecuencia_ideal:,.0f})', zorder=4)
    
    ax2.text(0, ceros, f'{ceros:,}', ha='center', va='bottom', fontweight='bold', fontsize=11)
    ax2.text(1, unos, f'{unos:,}', ha='center', va='bottom', fontweight='bold', fontsize=11)
    
    ax2.set_ylim(0, max(ceros, unos) * 1.15)
    
    ax2.legend()
    ax2.grid(axis='y', linestyle='--', alpha=0.7, zorder=0)
    
    plt.tight_layout()
    print("Generando gráficas...")
    plt.show()

if __name__ == '__main__':
    archivo_bin = r"Python Tests\out.bin" 
    
    analizar_binario_completo(archivo_bin, ancho_bitmap=256)