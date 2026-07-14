from elftools.elf.elffile import ELFFile
from pathlib import Path


def extract_patch(patch_file: Path):
    with open(patch_file, "rb") as f:
        elffile = ELFFile(f)
        text = elffile.get_section_by_name(".text")
        rodata = elffile.get_section_by_name(".bss")

        start = text["sh_offset"]
        end = rodata["sh_offset"] + rodata["sh_size"]

        f.seek(start)
        patch_data = f.read(end-start)
    print(f"Patch size: {len(patch_data)} bytes")

    with open(patch_file.parent / "build" / patch_file.with_suffix(".patch").name, "wb") as f:
        f.write(patch_data)
    return


if __name__ == "__main__":
    extract_patch(Path("infection.elf"))
