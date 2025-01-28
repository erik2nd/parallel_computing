# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import pandas as pd


def plot_data(file, image):
    try:
        data = pd.read_csv(file)
    except FileNotFoundError:
        print(f"Файл '{file}' не найден")
        return
    except pd.errors.EmptyDataError:
        print(f"Файл '{file}' пуст")
        return

    if "Threads" not in data.columns or "Time" not in data.columns:
        print(f"Файл '{file}' должен содержать столбцы 'Threads' и 'Time'")
        return

    plt.figure(figsize=(10, 6))
    plt.plot(data["Threads"], data["Time"], marker="*", linestyle="--", color="r", label="Время при потоках")
    plt.xlabel("Кол-во потоков", fontsize=12)
    plt.ylabel("Время выполнения (с)", fontsize=12)
    plt.title("Зависимость скорости выполнения от кол-ва потоков", fontsize=14)
    plt.grid(True)
    plt.legend()

    plt.savefig(image, dpi=300)
    plt.show()
    print(f"График сохранён в '{image}'.")


csv_file = "data.csv"
output_image = "data_plot.png"

plot_data(csv_file, output_image)
