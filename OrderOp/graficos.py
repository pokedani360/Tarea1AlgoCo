import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import re

file_path = '/home/dano/ejercicios/OrderOp/results.txt'

files = []
insertion_sort_times = []
merge_sort_times = []
quick_sort_times = []
cpp_sort_times = []

with open(file_path, 'r') as file:
    lines = file.readlines()

current_file = None
for line in lines:
    match = re.match(r'--- Procesando archivo: (.+) ---', line)
    if match:
        current_file = match.group(1)
        files.append(current_file)
        insertion_sort_times.append(None)
        merge_sort_times.append(None)
        quick_sort_times.append(None)
        cpp_sort_times.append(None)
        continue
    
    if current_file:
        if 'Insertion Sort' in line:
            time = int(re.search(r'took (\d+) milliseconds', line).group(1))
            insertion_sort_times[-1] = time
        elif 'Merge Sort' in line:
            time = int(re.search(r'took (\d+) milliseconds', line).group(1))
            merge_sort_times[-1] = time
        elif 'Quick Sort' in line:
            time = int(re.search(r'took (\d+) milliseconds', line).group(1))
            quick_sort_times[-1] = time
        elif 'C++ Standard Sort' in line:
            time = int(re.search(r'took (\d+) milliseconds', line).group(1))
            cpp_sort_times[-1] = time

data = pd.DataFrame({
    'File': files,
    'Insertion Sort': insertion_sort_times,
    'Merge Sort': merge_sort_times,
    'Quick Sort': quick_sort_times,
    'C++ Standard Sort': cpp_sort_times
})

print(data)

data_melted = data.melt(id_vars='File', var_name='Method', value_name='Time')

plt.figure(figsize=(14, 8))
sns.barplot(x='File', y='Time', hue='Method', data=data_melted)
plt.yscale('log')
plt.title('Comparación de Métodos de Ordenamiento (Escala Logarítmica)')
plt.xlabel('Archivos de Texto')
plt.ylabel('Tiempo de Ejecución (milisegundos)')
plt.xticks(rotation=90)
plt.legend(title='Método de Ordenamiento')
plt.tight_layout()
plt.savefig('/home/dano/ejercicios/OrderOp/ordenamiento_comparacion_log.png')
plt.show()

