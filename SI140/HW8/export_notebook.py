import json
import subprocess
import sys
from pathlib import Path

# Original notebook
#input your notebook path here
source = Path(
    r"HW8_Problem3_MonteCarlo_studentversion.ipynb"
)

# Read the notebook
notebook = json.loads(source.read_text(encoding="utf-8-sig"))

# Remove the nonstandard output field; preserve code, text and figures
removed = 0
for cell in notebook.get("cells", []):
    for output in cell.get("outputs", []):
        if "jetTransient" in output:
            del output["jetTransient"]
            removed += 1

# Save a separate cleaned copy
cleaned = source.with_name(source.stem + "_clean.ipynb")
cleaned.write_text(
    json.dumps(notebook, ensure_ascii=False, indent=1),
    encoding="utf-8"
)

print(f"Removed {removed} jetTransient fields.")
print(f"Cleaned notebook: {cleaned}")

# Export the cleaned copy to HTML
subprocess.run(
    [
        sys.executable,
        "-m",
        "nbconvert",
        "--to",
        "html",
        str(cleaned),
    ],
    check=True,
)

print(f"HTML file: {cleaned.with_suffix('.html')}")