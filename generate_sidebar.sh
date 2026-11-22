#!/usr/bin/env bash
# 根据 docs/ 目录结构重新生成根目录 _sidebar.md
#
# 用法（在项目根目录）:
#   bash generate_sidebar.sh
#   ./generate_sidebar.sh
#
# Windows（Git Bash）:
#   "D:\tool\Git\bin\bash.exe" generate_sidebar.sh

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DOCS_DIR="${SCRIPT_DIR}/docs"
OUTPUT="${SCRIPT_DIR}/_sidebar.md"
ROOT_KEY="__ROOT__"

is_root_excluded() {
  case "$1" in
    README.md|style.md) return 0 ;;
    *) return 1 ;;
  esac
}

sort_names() {
  LC_ALL=C sort -V
}

to_link() {
  printf './docs/%s' "${1//\\//}"
}

# DIRS[rel]=1
# FILES[rel]=换行分隔的 md 文件名（不含 README.md）
# CHILDREN[rel]=换行分隔的子目录名（顶级挂在 ROOT_KEY）
# HAS_README[rel]=1
declare -A DIRS=()
declare -A FILES=()
declare -A CHILDREN=()
declare -A HAS_README=()

append_unique() {
  local map_name="$1"
  local parent="$2"
  local value="$3"
  local list
  eval "list=\"\${${map_name}[\$parent]:-}\""
  case $'\n'"$list"$'\n' in
    *$'\n'"$value"$'\n'*) ;;
    *)
      if [[ -n "$list" ]]; then
        eval "${map_name}[\$parent]=\"\$list\"\$'\\n'\"\$value\""
      else
        eval "${map_name}[\$parent]=\"\$value\""
      fi
      ;;
  esac
}

scan() {
  local f rel dir name child parent cur
  local -a parts
  local i

  while IFS= read -r f; do
    rel="${f#"$DOCS_DIR"/}"
    rel="${rel#/}"
    name="${rel##*/}"
    if [[ "$rel" == */* ]]; then
      dir="${rel%/*}"
    else
      dir=""
    fi

    if [[ -n "$dir" ]]; then
      cur=""
      IFS='/' read -ra parts <<<"$dir"
      for ((i = 0; i < ${#parts[@]}; i++)); do
        child="${parts[$i]}"
        if [[ -n "$cur" ]]; then
          parent="$cur"
          cur="${cur}/${child}"
        else
          parent="$ROOT_KEY"
          cur="$child"
        fi
        DIRS["$cur"]=1
        append_unique CHILDREN "$parent" "$child"
      done
    fi

    if [[ "$name" == "README.md" ]]; then
      [[ -z "$dir" ]] && continue
      HAS_README["$dir"]=1
      continue
    fi

    if [[ -z "$dir" ]]; then
      is_root_excluded "$name" && continue
      append_unique FILES "$ROOT_KEY" "$name"
    else
      append_unique FILES "$dir" "$name"
    fi
  done < <(find "$DOCS_DIR" -type f -name '*.md' | sed 's|\\|/|g')
}

emit_dir() {
  local rel="$1"
  local indent="$2"
  local name path kind
  local -A is_dir_child=()
  local -A is_file_child=()
  local names=""

  if [[ -n "${CHILDREN[$rel]+x}" ]]; then
    while IFS= read -r name; do
      [[ -z "$name" ]] && continue
      is_dir_child["$name"]=1
      names="${names}${names:+$'\n'}${name}"
    done < <(printf '%s\n' "${CHILDREN[$rel]}")
  fi
  if [[ -n "${FILES[$rel]+x}" ]]; then
    while IFS= read -r name; do
      [[ -z "$name" ]] && continue
      is_file_child["$name"]=1
      names="${names}${names:+$'\n'}${name}"
    done < <(printf '%s\n' "${FILES[$rel]}")
  fi

  [[ -z "$names" ]] && return

  while IFS= read -r name; do
    [[ -z "$name" ]] && continue
    if [[ -n "${is_dir_child[$name]+x}" ]]; then
      if [[ "$rel" == "$ROOT_KEY" ]]; then
        path="$name"
      else
        path="${rel}/${name}"
      fi
      [[ -n "${DIRS[$path]+x}" ]] || continue
      if [[ -n "${HAS_README[$path]+x}" ]]; then
        printf '%s* [%s](%s)\n' "$indent" "$name" "$(to_link "${path}/README.md")"
      else
        printf '%s* %s\n' "$indent" "$name"
      fi
      emit_dir "$path" "${indent}  "
    elif [[ -n "${is_file_child[$name]+x}" ]]; then
      if [[ "$rel" == "$ROOT_KEY" ]]; then
        printf '%s- [%s](%s)\n' "$indent" "${name%.md}" "$(to_link "$name")"
      else
        printf '%s- [%s](%s)\n' "$indent" "${name%.md}" "$(to_link "${rel}/${name}")"
      fi
    fi
  done < <(printf '%s\n' "$names" | sort_names)
}

main() {
  if [[ ! -d "$DOCS_DIR" ]]; then
    echo "错误: 找不到 docs 目录: $DOCS_DIR" >&2
    exit 1
  fi

  echo "扫描 docs/ ..."
  scan

  local tmp name path
  tmp="$(mktemp)"
  {
    printf '%s\n\n' "<!-- 本文件由 generate_sidebar.sh 根据 docs/ 自动生成，请勿手改 -->"

    if [[ -n "${CHILDREN[$ROOT_KEY]+x}" ]]; then
      while IFS= read -r name; do
        [[ -z "$name" ]] && continue
        path="$name"
        [[ -n "${DIRS[$path]+x}" ]] || continue
        if [[ -n "${HAS_README[$path]+x}" ]]; then
          printf '* [%s](%s)\n' "$name" "$(to_link "${path}/README.md")"
        else
          printf '* %s\n' "$name"
        fi
        emit_dir "$path" "  "
        printf '\n'
      done < <(printf '%s\n' "${CHILDREN[$ROOT_KEY]}" | sort_names)
    fi

    if [[ -n "${FILES[$ROOT_KEY]+x}" ]]; then
      while IFS= read -r name; do
        [[ -z "$name" ]] && continue
        printf '* [%s](%s)\n\n' "${name%.md}" "$(to_link "$name")"
      done < <(printf '%s\n' "${FILES[$ROOT_KEY]}" | sort_names)
    fi
  } >"$tmp"

  mv "$tmp" "$OUTPUT"
  echo "已生成: $OUTPUT"
  echo "条目数: $(grep -cE '^\s*[*-] ' "$OUTPUT" || true)"
}

main "$@"
