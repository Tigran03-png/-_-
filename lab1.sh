#!/bin/bash


if [ $# -ne 2 ]; then
  echo "Использование: $0 <папка> <макс_размер_в_байтах>"
  exit 1
fi

FOLDER=$1
MAX_SIZE=$2


if [ ! -d "$FOLDER" ]; then
  echo "Ошибка: '$FOLDER' не является директорией"
  exit 1
fi


archive_file() {
  local file="$1"
  local archive="${file}.tar"
  tar -cf "$archive" "$file" && echo "Архив создан: $archive"
}


find "$FOLDER" -type f | while read -r file; do
  size=$(stat -c%s "$file")
  if [ "$size" -gt "$MAX_SIZE" ]; then
    archive_file "$file"
  fi
done
