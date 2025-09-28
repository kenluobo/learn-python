#!/usr/bin/env python3
import os
import re
import sys

HEADER_TEMPLATE = """#ifndef {GUARD}
#define {GUARD}

#include \"TableBase.h\"

struct {StructName} : TableItem {{
  {StructName}() = default;
  {StructName}(const char *keyId, const char *csv)
      : TableItem(keyId, csv) {{
    fill_data();
  }}

  static const std::string &get_table_name() {{
    static const std::string kTableName = \"{DisplayName}\";
    return kTableName;
  }}

 protected:
  void fill_data() override {{
{FILL_BODY}
  }}

 public:
{FIELDS}
}};

#endif
"""

FIELD_TEMPLATE = "  std::string {name};"
ASSIGNMENT_TEMPLATE = "      {field} = dataVec.at({index});"
FILL_BODY_TEMPLATE = """    try {{
{ASSIGNMENTS}
    }} catch (const std::out_of_range &) {{
      // ignore or log
    }}"""

TABLES_HEADER_TEMPLATE = """#ifndef TABLES_H
#define TABLES_H

#include \"def/TableBase.h\"
{INCLUDES}

#endif // TABLES_H
"""


def to_pascal_case(name: str) -> str:
    parts = [p for p in re.split(r"[^a-zA-Z0-9]", name) if p]
    if not parts:
        return ""
    return "".join(p[:1].upper() + p[1:] for p in parts)


def to_upper_guard(name: str) -> str:
    cleaned = re.sub(r"[^a-zA-Z0-9]", "_", name)
    cleaned = re.sub(r"__+", "_", cleaned)
    cleaned = cleaned.strip("_")
    if not cleaned:
        cleaned = "TABLE"
    return f"{cleaned.upper()}_H"


def generate_table_header(table, cols, out_dir):
    display_name = to_pascal_case(table)
    struct_name = f"{display_name}TableItem"
    guard = to_upper_guard(table)
    fields = "\n".join(FIELD_TEMPLATE.format(name=c) for c in cols)
    assignments = "\n".join(
        ASSIGNMENT_TEMPLATE.format(field=c, index=i) for i, c in enumerate(cols)
    )
    fill_body = FILL_BODY_TEMPLATE.format(ASSIGNMENTS=assignments)

    content = HEADER_TEMPLATE.format(
        GUARD=guard,
        StructName=struct_name,
        DisplayName=display_name,
        FILL_BODY=fill_body,
        FIELDS=fields,
    )

    filename = os.path.join(out_dir, f"{display_name}.h")
    with open(filename, "w", encoding="utf-8") as out:
        out.write(content)
    print(f"Generated {filename}")
    return filename


def generate_tables_header(headers, out_dir):
    includes = "\n".join(
        f"#include \"def/{os.path.basename(h)}\"" for h in sorted(headers)
    )
    includes = f"\n{includes}" if includes else ""
    content = TABLES_HEADER_TEMPLATE.format(INCLUDES=includes)

    filename = os.path.join(out_dir, "tables.h")
    with open(filename, "w", encoding="utf-8") as out:
        out.write(content)
    print(f"Generated {filename}")


def generate_table_base(template_path, out_dir):
    destination = os.path.join(out_dir, "def", "TableBase.h")
    with open(template_path, "r", encoding="utf-8") as src, open(
        destination, "w", encoding="utf-8"
    ) as dst:
        dst.write(src.read())
    print(f"Generated {destination}")


def main(config_path, out_dir):
    def_dir = os.path.join(out_dir, "def")
    os.makedirs(def_dir, exist_ok=True)

    headers = []

    template_dir = os.path.dirname(config_path)
    table_base_template = os.path.join(template_dir, "TableBase.h.in")
    if os.path.exists(table_base_template):
        generate_table_base(table_base_template, out_dir)

    with open(config_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.split("#", 1)[0].strip()
            if not line:
                continue

            table, cols = line.split(":", 1)
            table = table.strip().strip('"')
            cols = [c.strip().strip('"') for c in cols.split(",") if c.strip()]

            if not table or not cols:
                continue

            hfile = generate_table_header(table, cols, def_dir)
            headers.append(hfile)

    generate_tables_header(headers, out_dir)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: gen_all_headers.py <config.in> <out_dir>")
        sys.exit(1)
    main(sys.argv[1], sys.argv[2])
