# Roman Numeral Parser & Converter (Lookup-Free)

## Overview

This is a robust, lookup-free Roman numeral parser and converter built entirely from first principles. Unlike most existing tools, it performs structural validation and symbolic interpretation without relying on hardcoded tables of Roman numeral values or patterns.

The parser is capable of:
- Converting **Roman numerals to integers** with full grammatical validation
- Converting **integers to Roman numerals** using arithmetic and offset logic
- Enforcing **Roman numeral rules**: descending order, valid subtractive pairs, and exclusive use of subtractive values

It is designed as both an educational tool and a demonstration of low-level grammar enforcement in symbolic systems.

---

## Features

✅ Fully symbolic Roman numeral parsing  
✅ No lookup tables—everything is derived from 7 base symbols  
✅ Structural validation of:
- Subtractive legality (e.g. `I` only before `V` or `X`)
- Repetition rules (`I`, `X`, `C`, `M` repeat up to 3 times)
- Illegal constructs (`IC`, `VV`, `XIXIX`, etc.)  
✅ Forward parsing and full grammar enforcement  
✅ Scalable up to 3999+ and beyond

---

## Example

```bash
Roman numeral: MMCMXCIX
Parsed integer: 2999

Integer: 2743
Roman numeral: MMDCCXLIII

Invalid: MCMC → rejected (structurally incorrect)
