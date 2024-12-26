# Установить выходной формат (PNG)
set terminal png size 800,600
set output "complexity_plot.png"

# Настройка графика
set title "Сравнение алгоритмов Дейкстры"
set xlabel "Количество вершин"
set ylabel "Время выполнения (мс)"
set grid
set key top left
set xrange [0:1000]  # Установите диапазон X (количество вершин)
set yrange [0:100]   # Установите диапазон Y (время выполнения)


# Загрузка данных и построение графика
plot "complexity.dat" using 1:2 with linespoints title "Логарифмический алгоритм", \
     "complexity.dat" using 1:3 with linespoints title "Простой алгоритм"
plot "complexity.dat" using 1:2 with linespoints lw 2 lc "red" title "Логарифмический алгоритм", \
     "complexity.dat" using 1:3 with linespoints lw 2 lc "blue" title "Простой алгоритм"

