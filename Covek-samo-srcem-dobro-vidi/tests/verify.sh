#!/usr/bin/env bash
#
# Verification suite: confirms the project built and the analysis engine behaves.
#
#   bash tests/verify.sh [BUILD_DIR]
#
# BUILD_DIR defaults to $BUILD_DIR env var, then ./build.

set -euo pipefail

BUILD_DIR="${1:-${BUILD_DIR:-build}}"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

STEGCLI="$BUILD_DIR/tools/stegcli"
GUI="$BUILD_DIR/gui/Covek-samo-srcem-dobro-vidi"

fail() { echo "FAIL: $*" >&2; exit 1; }
pass() { echo "PASS: $*"; }

# --- 1. build produced the expected binaries -------------------------------
[ -x "$STEGCLI" ] || fail "stegcli not found at $STEGCLI"
[ -x "$GUI" ] || fail "GUI binary not found at $GUI"
pass "stegcli and GUI binaries present"

python3 "$HERE/make_samples.py" "$WORK"

# --- 2. clean image: engine runs, reports nothing appended -----------------
echo "--- stegcli $WORK/clean.png ---"
clean_out="$("$STEGCLI" "$WORK/clean.png")"
echo "$clean_out"
grep -q "format: png" <<<"$clean_out" || fail "clean.png not recognised as PNG"
grep -q "Trailing bytes: 0" <<<"$clean_out" || fail "clean.png should report no trailing data"
pass "clean image: format detected, no trailing data"

# --- 3. tampered image: trailing data + signature detected -----------------
echo "--- stegcli $WORK/trailing.png ---"
trail_out="$("$STEGCLI" "$WORK/trailing.png")"
echo "$trail_out"
grep -q "verdict: positive" <<<"$trail_out" || fail "trailing.png should get a positive verdict"
grep -qi "ZIP archive" <<<"$trail_out" || fail "trailing.png should flag the ZIP signature"
pass "appended data + ZIP signature detected"

# --- 4. Qt GUI links and constructs (no display) ---------------------------
echo "--- GUI --selftest ---"
if QT_QPA_PLATFORM=offscreen "$GUI" --selftest 2>/dev/null; then
    pass "Qt GUI constructs under the offscreen platform"
elif QT_QPA_PLATFORM=minimal "$GUI" --selftest; then
    pass "Qt GUI constructs under the minimal platform"
else
    fail "GUI --selftest did not exit cleanly"
fi

echo
echo "ALL CHECKS PASSED"
