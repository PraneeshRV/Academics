---
type: lab-record
course: Web Application Security
semester: 7
lab: 3
title: XML, XML Schema, JSON, AJAX and Fetch API
date: 2026-07-27
status: complete
---

# Lab 3 — XML, XML Schema, JSON, AJAX and Fetch API

All five activities and the challenge exercise, implemented and run against PHP 8.5.8.

## How to run

The pages call PHP endpoints, so they must be served, not opened with `file://`.
From this folder:

```bash
php -S localhost:8080
```

Then open <http://localhost:8080/> and use the links on the index page.

Schema validation runs from the terminal:

```bash
php validate.php
```

```bash
php validate.php students_invalid.xml
```

## Files

| File | Purpose |
|---|---|
| `students.xml` | Activity 1 — five student records |
| `students.xsd` | Activity 2 — schema with range restrictions |
| `students_invalid.xml` | Deliberately invalid data, proves the schema rejects it |
| `validate.php` | CLI validator (`DOMDocument::schemaValidate`) |
| `students.json` | Activity 3 — JSON array of five students |
| `students.php` | JSON endpoint (hard-coded array) for Activities 4 and 5 |
| `ajax.html` | Activity 4 — XMLHttpRequest into an HTML table |
| `fetch.html` | Activity 5 — Fetch API into an HTML table |
| `students_from_xml.php` | Challenge backend — XML → validate → SimpleXML → JSON |
| `viewer.html` | Challenge frontend — Student Information Viewer |
| `index.html` | Landing page linking every deliverable |

## Activity 1 — XML document

`students.xml` holds one root element `<students>` with five `<student>` children.
Each record has `registerNumber`, `name`, `department`, `semester` and `cgpa`.

Syntax rules followed: exactly one root element, matching closing tags, correct
nesting, and case-consistent tag names.

## Activity 2 — Schema restrictions

The required restrictions are expressed as named simple types:

```xml
<xs:simpleType name="semesterType">
    <xs:restriction base="xs:integer">
        <xs:minInclusive value="1"/>
        <xs:maxInclusive value="8"/>
    </xs:restriction>
</xs:simpleType>

<xs:simpleType name="cgpaType">
    <xs:restriction base="xs:decimal">
        <xs:minInclusive value="0"/>
        <xs:maxInclusive value="10"/>
        <xs:fractionDigits value="2"/>
    </xs:restriction>
</xs:simpleType>
```

Three extra integrity rules are included: `registerNumber` must match `CB[0-9]{5}`,
`department` must come from an enumeration, and `xs:unique` blocks duplicate register
numbers.

### Verification output

`php validate.php` on the good file:

```
VALID: students.xml conforms to students.xsd
```

`php validate.php students_invalid.xml` on the deliberately broken file:

```
INVALID: students_invalid.xml violates students.xsd
  line 14: Element 'department': [facet 'enumeration'] The value 'CIVIL' is not an element of the set {'CSE', 'IT', 'ECE', 'EEE', 'MECH'}.
  line 15: Element 'semester': [facet 'maxInclusive'] The value '12' is greater than the maximum value allowed ('8').
  line 16: Element 'cgpa': [facet 'maxInclusive'] The value '11.5' is greater than the maximum value allowed ('10').
```

This is the point of the activity: `<semester>Five</semester>` and `<semester>12</semester>`
are both well-formed XML, and only the schema catches them.

## Activity 3 — JSON

`students.json` is a JSON array of five objects. The same five records as the XML file,
in roughly a third of the bytes (663 B vs 1.1 KB), which is the practical argument for
JSON in APIs.

## Activity 4 — AJAX

`students.php` sets `Content-Type: application/json` and echoes `json_encode($students)`.
`ajax.html` requests it with `XMLHttpRequest`, parses the body with `JSON.parse()`, and
builds the table.

Two error paths are handled, and they are not the same thing:

- `xhr.onerror` fires only when the request never reaches the server (DNS failure,
  connection refused).
- `xhr.onload` fires for **any** completed response, including 404 and 500, so the
  handler checks `xhr.status !== 200` before parsing.

## Activity 5 — Fetch API

`fetch.html` does the same work with `fetch()`. The equivalent trap applies:

> `fetch()` rejects only on network failure. A 404 or a 500 still resolves, with
> `response.ok === false`.

So the status is checked explicitly and a failure is thrown into `.catch()`, which
renders "Unable to retrieve student data."

## Challenge — Student Information Viewer

Pipeline: `students.xml` → schema validation → `simplexml_load_file()` →
`json_encode()` → `fetch()` → table, with no page reload.

`students_from_xml.php` validates before reading, so malformed or out-of-range data is
rejected at the server with HTTP 500 and a JSON error body instead of reaching the browser.

One implementation detail worth keeping: **do not call `json_encode($xml)` directly on a
SimpleXMLElement.** Every value comes out as a string, and a document containing a single
`<student>` collapses into an object instead of a one-element array. The script loops and
builds a plain PHP array with `(int)` and `(float)` casts, so `semester` and `cgpa` stay
numeric in the JSON.

### Security note (relevant to this course)

`ajax.html` and `fetch.html` build the table with string concatenation into `innerHTML`,
which is the pattern in the lab handout. That is a stored-XSS sink: a student name of
`<img src=x onerror=alert(1)>` coming back from the server would execute.

`viewer.html` therefore builds the table with `createElement` and `textContent`, which
inserts the same value as text and cannot execute. The schema's `nameType` restriction is
defence in depth, not a substitute — validation limits what enters the XML, escaping is
what makes output safe.

## XML vs JSON

| XML | JSON |
|---|---|
| Tag based | Key-value based |
| Verbose | Compact |
| Larger file size | Smaller file size |
| Slower parsing | Faster parsing |
| Schema validation built in (XSD) | No built-in schema (JSON Schema is a separate spec) |

## AJAX vs Fetch

| XMLHttpRequest | Fetch API |
|---|---|
| Callback based | Promise based |
| Manual `JSON.parse(xhr.responseText)` | `response.json()` |
| Verbose setup (`open`, `onload`, `send`) | Single call, chained `.then()` |
| Non-2xx status must be checked manually | Non-2xx status must **also** be checked manually |

The last row is the common exam trick: switching to Fetch does not give you automatic
HTTP error handling. Neither API treats a 404 as an error on its own.

## Verification record

Server: `php -S localhost:8080` in this folder. Every result below was observed in a
browser, not assumed.

| Check | Result |
|---|---|
| `php validate.php` | `VALID` (exit 0) |
| `php validate.php students_invalid.xml` | `INVALID`, 3 facet violations, exit 1 |
| `ajax.html` → Load Students | Table rendered, 5 rows, CB22001–CB22005 |
| `fetch.html` → Load Students | Table rendered, 5 rows |
| `viewer.html` → Load Students | Table rendered, 5 rows, "5 student record(s) loaded." |
| `viewer.html` with `students.xml` removed | "Unable to retrieve student data: students.xml not found on the server." |
| `curl students_from_xml.php` | `"semester":5,"cgpa":8.92` — numeric, top level is an array |
| `json_encode(simplexml_load_file(...))` for contrast | `{"student":[{...,"semester":"5","cgpa":"8.92"}]}` — strings, wrapped in an object |
