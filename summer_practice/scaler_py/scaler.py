"""
    python main.py https://ru.wikipedia.org
    python main.py https://ru.wikipedia.org --tag p --output result.txt
"""

import argparse
import sys
import requests
from bs4 import BeautifulSoup


def scrape_website(url: str, timeout: int = 10) -> BeautifulSoup | None:
    headers = {
        "User-Agent": (
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
            "AppleWebKit/537.36 (KHTML, like Gecko) "
            "Chrome/125.0 Safari/537.36"
        )
    }

    try:
        response = requests.get(url, headers=headers, timeout=timeout)
        response.raise_for_status()
    except requests.exceptions.RequestException as e:
        print(f"Ошибка при запросе к {url}: {e}")
        return None

    response.encoding = response.apparent_encoding
    return BeautifulSoup(response.text, "html.parser")


def extract_data(soup: BeautifulSoup, tag: str = "h1") -> list[str]:
    elements = soup.find_all(tag)
    result = []
    for el in elements:
        text = el.get_text(strip=True)
        if text:
            result.append(text)
    return result


def save_data_to_file(data: list[str], filename: str) -> None:
    with open(filename, "w", encoding="utf-8") as file:
        file.write("\n".join(data))


def main() -> None:
    parser = argparse.ArgumentParser(description="Простой веб-скрейпер")
    parser.add_argument("url", help="Адрес страницы, которую нужно спарсить")
    parser.add_argument(
        "--tag", default="h1", help="HTML-тег для извлечения (по умолчанию h1)"
    )
    parser.add_argument(
        "--output", default="result.txt", help="Имя файла для сохранения результата"
    )
    args = parser.parse_args()

    soup = scrape_website(args.url)
    if soup is None:
        sys.exit(1)

    data = extract_data(soup, args.tag)

    if not data:
        print(f"На странице не найдено элементов <{args.tag}>.")
        sys.exit(0)

    save_data_to_file(data, args.output)
    print(f"Найдено {len(data)} элементов <{args.tag}>. Сохранено в {args.output}")


if __name__ == "__main__":
    main()
