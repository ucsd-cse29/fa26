#!/usr/bin/env bash
set -euo pipefail

echo "===================================="
echo "Blender Addon Updater"
echo "===================================="

for f in "config.yml" "addon_update.py"; do
    if [[ ! -f "$f" ]]; then
        echo "ERROR: $f not found!"
        exit 1
    fi
done

parse_yml_value() {
    local key="$1"
    grep -E "^${key}[[:space:]]*:" config.yml | head -1 | sed -E "s/^${key}[[:space:]]*:[[:space:]]*//;s/['\"]//g;s/[[:space:]]*$//"
}

BLENDER_EXE=$(parse_yml_value "blender_executable")
BLEND_FILE=$(parse_yml_value "blend_file")
ADDON_FOLDER=$(parse_yml_value "addon_folder")
OUTPUT_ZIP=$(parse_yml_value "output_zip")
ADDON_NAME=$(parse_yml_value "addon_name")
VERBOSE=$(parse_yml_value "verbose")

for var in BLENDER_EXE BLEND_FILE ADDON_FOLDER ADDON_NAME; do
    if [[ -z "${!var}" ]]; then
        key=$(echo "$var" | sed 's/_EXE$//' | tr '[:upper:]' '[:lower:]' | sed 's/blender/blender_executable/;s/blend/blend_file/;s/addon_folder/addon_folder/;s/addon_name/addon_name/')
        echo "ERROR: $var not found in config.yml"
        exit 1
    fi
done

[[ -z "$OUTPUT_ZIP" ]] && OUTPUT_ZIP="${ADDON_FOLDER}.zip"

if [[ "$VERBOSE" == "true" ]]; then
    echo "Configuration loaded:"
    echo "  Blender:      $BLENDER_EXE"
    echo "  Blend file:   $BLEND_FILE"
    echo "  Addon folder: $ADDON_FOLDER"
    echo "  Output zip:   $OUTPUT_ZIP"
    echo "  Addon name:   $ADDON_NAME"
    echo
fi

if [[ ! -f "$BLENDER_EXE" ]]; then
    echo "ERROR: Blender executable not found: $BLENDER_EXE"
    exit 1
fi
if [[ ! -d "$ADDON_FOLDER" ]]; then
    echo "ERROR: Addon folder not found: $ADDON_FOLDER"
    exit 1
fi
if [[ ! -f "$BLEND_FILE" ]]; then
    echo "ERROR: Blend file not found: $BLEND_FILE"
    exit 1
fi

echo "[1/3] Creating zip file from addon folder..."
[[ -f "$OUTPUT_ZIP" ]] && rm "$OUTPUT_ZIP"

parent_dir=$(dirname "$ADDON_FOLDER")
folder_name=$(basename "$ADDON_FOLDER")
(cd "$parent_dir" && zip -rq "$(realpath --relative-to="$parent_dir" "$(pwd)")/../$(basename "$OUTPUT_ZIP")" "$folder_name") || \
    zip -rq "$OUTPUT_ZIP" "$ADDON_FOLDER"

if [[ ! -f "$OUTPUT_ZIP" ]]; then
    echo "ERROR: Failed to create zip file"
    exit 1
fi
echo "Successfully created: $OUTPUT_ZIP"

echo "[2/3] Running Blender addon update script..."
if [[ "$VERBOSE" == "true" ]]; then
    echo "Running: \"$BLENDER_EXE\" \"$BLEND_FILE\" --background --python \"addon_update.py\""
fi

if ! "$BLENDER_EXE" "$BLEND_FILE" --background --python "addon_update.py"; then
    echo "ERROR: Blender script execution failed"
    echo "Check the console output above for details"
    exit 1
fi
echo "Addon update script completed successfully!"

echo "[3/3] Restarting Blender..."
"$BLENDER_EXE" "$BLEND_FILE" &
disown

echo
echo "===================================="
echo "Update Successful!"
echo "===================================="
echo "  Addon folder zipped: $OUTPUT_ZIP"
echo "  Addon reinstalled:   $ADDON_NAME"
echo "  Blender restarted with: $BLEND_FILE"
echo

if [[ "$VERBOSE" == "true" ]]; then
    read -rp "Press enter to exit..."
fi
