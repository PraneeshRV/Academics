# FORENSICS LAB EVAL - COMPLETE CHEATSHEET

## STEP 0: EXTRACT YOUR SET
```bash
cd /home/praneesh/Praneesh/Academics/Sem6/Forensics/LabEval
unzip -P <PASSWORD> Set_X.zip
```

---

## SET A: NTFS Undelete + Encrypted PDF
**Files:** `7-undel-ntfs.zip` (191 KiB), `Set_A_enc.pdf` (34 KiB)

### 1. Crack Encrypted PDF
```bash
# Extract PDF hash for cracking
pdf2john Set_A/Set_A_enc.pdf > pdf_hash.txt
john pdf_hash.txt --wordlist=/usr/share/wordlists/rockyou.txt
# OR
john pdf_hash.txt --show

# Once password found, decrypt:
qpdf --password=<FOUND_PASSWORD> --decrypt Set_A/Set_A_enc.pdf Set_A/Set_A_dec.pdf
# OR use pikepdf:
python3 -c "import pikepdf; pdf=pikepdf.open('Set_A/Set_A_enc.pdf',password='<PWD>'); pdf.save('Set_A/Set_A_dec.pdf')"
# View PDF
evince Set_A/Set_A_dec.pdf &
```

### 2. NTFS Undelete (Recover Deleted Files)
```bash
# Unzip the NTFS image
unzip Set_A/7-undel-ntfs.zip -d Set_A/
# or if nested:
cd Set_A && unzip 7-undel-ntfs.zip

# Check what's inside (find the .img/.dd file)
file Set_A/7-undel-ntfs*

# List partitions
mmls Set_A/<image_file>

# If raw NTFS partition (no partition table):
fls -r -p Set_A/<image_file>
# If partition table found, use offset:
fls -r -p -o <offset> Set_A/<image_file>

# List deleted files only (look for * prefix)
fls -r -p -d Set_A/<image_file>

# Recover a specific deleted file by inode:
icat Set_A/<image_file> <inode_number> > recovered_file

# Recover ALL deleted files:
tsk_recover -e Set_A/<image_file> Set_A/recovered/

# Alternative: ntfsundelete
ntfsundelete Set_A/<image_file> --scan
ntfsundelete Set_A/<image_file> --undelete --match "*.txt" --output Set_A/recovered/

# Carve files (foremost/scalpel)
foremost -t all -i Set_A/<image_file> -o Set_A/carved/
# OR
scalpel Set_A/<image_file> -o Set_A/carved/

# Check file system info
fsstat Set_A/<image_file>

# Search for strings
strings Set_A/<image_file> | grep -i "flag\|secret\|password\|key"
```

---

## SET B: SQLite DB + SQL + Encrypted PDF + EVTX
**Files:** `downloads.db` (24 KiB), `sample.sql` (9.1 KiB), `Set_B_enc.pdf` (74 KiB), `slog.evtx` (20 MiB)

### 1. Crack Encrypted PDF
```bash
pdf2john Set_B/Set_B_enc.pdf > pdf_hash_B.txt
john pdf_hash_B.txt --wordlist=/usr/share/wordlists/rockyou.txt
john pdf_hash_B.txt --show
qpdf --password=<PWD> --decrypt Set_B/Set_B_enc.pdf Set_B/Set_B_dec.pdf
evince Set_B/Set_B_dec.pdf &
```

### 2. Analyze downloads.db (SQLite)
```bash
# List all tables
sqlite3 Set_B/downloads.db ".tables"

# Show schema
sqlite3 Set_B/downloads.db ".schema"

# Dump everything
sqlite3 Set_B/downloads.db ".dump"

# Common browser download queries
sqlite3 Set_B/downloads.db "SELECT * FROM downloads;"
sqlite3 Set_B/downloads.db "SELECT url, filename, start_time, end_time, total_bytes FROM downloads;"

# Check for suspicious downloads
sqlite3 Set_B/downloads.db "SELECT * FROM downloads WHERE url LIKE '%exe%' OR url LIKE '%suspicious%';"

# Export to CSV
sqlite3 -header -csv Set_B/downloads.db "SELECT * FROM downloads;" > downloads_export.csv
```

### 3. Analyze sample.sql
```bash
# Read it directly
cat Set_B/sample.sql

# Import into temp sqlite DB and query
sqlite3 /tmp/sample_B.db < Set_B/sample.sql
sqlite3 /tmp/sample_B.db ".tables"
sqlite3 /tmp/sample_B.db ".dump"
```

### 4. Analyze slog.evtx (Windows Event Log)
```bash
# Parse EVTX to XML
python3 -c "
import Evtx.Evtx as evtx
import Evtx.Views as e_views
with evtx.Evtx('Set_B/slog.evtx') as log:
    print(e_views.XML_HEADER)
    print('<Events>')
    for record in log.records():
        print(record.xml())
    print('</Events>')
" > Set_B/slog.xml 2>/dev/null

# Count total events
python3 -c "
import Evtx.Evtx as evtx
with evtx.Evtx('Set_B/slog.evtx') as log:
    records = list(log.records())
    print(f'Total events: {len(records)}')
"

# Search for specific Event IDs (security-related)
# 4624=Logon, 4625=Failed Logon, 4648=Explicit Creds, 4672=Admin Logon
# 4688=Process Create, 4689=Process Exit, 1102=Log Clear
# 7045=Service Install, 4697=Service Install
grep -i "EventID" Set_B/slog.xml | sort | uniq -c | sort -rn | head -20

# Search for keywords
grep -i "flag\|password\|secret\|malware\|hack\|suspicious" Set_B/slog.xml

# Filter by specific EventID
python3 -c "
import Evtx.Evtx as evtx
import xml.etree.ElementTree as ET
target_ids = ['4624','4625','4648','4672','4688','7045','1102','4697']
with evtx.Evtx('Set_B/slog.evtx') as log:
    for record in log.records():
        xml = record.xml()
        try:
            root = ET.fromstring(xml)
            ns = '{http://schemas.microsoft.com/win/2004/08/events/event}'
            eid = root.find(f'.//{ns}EventID').text
            if eid in target_ids:
                print(f'=== Event {eid} ===')
                print(xml[:500])
                print()
        except: pass
"

# Quick strings search on raw EVTX
strings Set_B/slog.evtx | grep -i "flag\|secret\|password\|cmd\|powershell\|base64"
```

---

## SET C: NTFS Undelete + Encrypted PDF + USB Disk Image
**Files:** `7-undel-ntfs.zip` (191 KiB), `Set_B_enc.pdf` (32 KiB), `usb_dd.7z` (35 MiB)

### 1. Crack Encrypted PDF
```bash
pdf2john Set_C/Set_B_enc.pdf > pdf_hash_C.txt
john pdf_hash_C.txt --wordlist=/usr/share/wordlists/rockyou.txt
john pdf_hash_C.txt --show
qpdf --password=<PWD> --decrypt Set_C/Set_B_enc.pdf Set_C/Set_C_dec.pdf
evince Set_C/Set_C_dec.pdf &
```

### 2. NTFS Undelete (same as Set A)
```bash
unzip Set_C/7-undel-ntfs.zip -d Set_C/
# Then follow same steps as Set A above
fls -r -p -d Set_C/<image_file>
tsk_recover -e Set_C/<image_file> Set_C/recovered/
foremost -t all -i Set_C/<image_file> -o Set_C/carved/
strings Set_C/<image_file> | grep -i "flag\|secret\|password"
```

### 3. Analyze USB Disk Image
```bash
# Extract 7z
7z x Set_C/usb_dd.7z -oSet_C/

# Identify image type
file Set_C/usb_dd*

# Partition layout
mmls Set_C/usb_dd*

# File system info
fsstat Set_C/usb_dd*
# With offset if needed:
fsstat -o <offset> Set_C/usb_dd*

# List ALL files (including deleted)
fls -r -p Set_C/usb_dd*
fls -r -p -d Set_C/usb_dd*    # deleted only

# Recover ALL files
tsk_recover -e Set_C/usb_dd* Set_C/usb_recovered/

# Carve files
foremost -t all -i Set_C/usb_dd* -o Set_C/usb_carved/

# Search for strings/flags
strings Set_C/usb_dd* | grep -i "flag\|secret\|password\|key\|hidden"

# Bulk extractor (finds emails, URLs, credit cards, etc.)
bulk_extractor -o Set_C/bulk_out/ Set_C/usb_dd*

# Check with binwalk for hidden/embedded files
binwalk Set_C/usb_dd*
binwalk -e Set_C/usb_dd*

# Timeline analysis
fls -r -p -m "/" Set_C/usb_dd* > Set_C/bodyfile.txt
mactime -b Set_C/bodyfile.txt > Set_C/timeline.csv

# Mount the image (read-only)
sudo mkdir -p /mnt/usb_evidence
sudo mount -o ro,loop,offset=$((512*<START_SECTOR>)) Set_C/usb_dd* /mnt/usb_evidence
ls -la /mnt/usb_evidence/
# Don't forget to unmount: sudo umount /mnt/usb_evidence
```

---

## SET D: EVTX + SMS DB + SQL + Encrypted PDF
**Files:** `alog.evtx` (20 MiB), `mmssms.db` (100 KiB, password-protected), `sample.sql` (1.6 KiB), `Set_D_enc.pdf` (49 KiB)

### 1. Crack Encrypted PDF
```bash
pdf2john Set_D/Set_D_enc.pdf > pdf_hash_D.txt
john pdf_hash_D.txt --wordlist=/usr/share/wordlists/rockyou.txt
john pdf_hash_D.txt --show
qpdf --password=<PWD> --decrypt Set_D/Set_D_enc.pdf Set_D/Set_D_dec.pdf
evince Set_D/Set_D_dec.pdf &
```

### 2. Analyze alog.evtx (same approach as Set B slog.evtx)
```bash
python3 -c "
import Evtx.Evtx as evtx
import Evtx.Views as e_views
with evtx.Evtx('Set_D/alog.evtx') as log:
    print(e_views.XML_HEADER)
    print('<Events>')
    for record in log.records():
        print(record.xml())
    print('</Events>')
" > Set_D/alog.xml 2>/dev/null

# Count events
python3 -c "
import Evtx.Evtx as evtx
with evtx.Evtx('Set_D/alog.evtx') as log:
    print(f'Total: {len(list(log.records()))}')
"

# Event ID distribution
grep -oP 'EventID[^<]*>\K[^<]+' Set_D/alog.xml | sort | uniq -c | sort -rn | head -20

# Search for interesting stuff
strings Set_D/alog.evtx | grep -i "flag\|secret\|password\|cmd\|powershell\|base64"
grep -i "flag\|password\|secret\|malware\|hack" Set_D/alog.xml
```

### 3. Analyze mmssms.db (Android SMS Database)
```bash
# This DB might be password-protected (SQLCipher)
# First try plain sqlite:
sqlite3 Set_D/mmssms.db ".tables" 2>&1

# If it works (not encrypted):
sqlite3 Set_D/mmssms.db ".schema"
sqlite3 Set_D/mmssms.db "SELECT * FROM sms;" 2>/dev/null
sqlite3 Set_D/mmssms.db "SELECT address, body, date, type FROM sms;" 2>/dev/null
# type: 1=received, 2=sent

# List all threads
sqlite3 Set_D/mmssms.db "SELECT * FROM threads;" 2>/dev/null

# MMS parts
sqlite3 Set_D/mmssms.db "SELECT * FROM part;" 2>/dev/null

# If SQLCipher encrypted, try:
# sqlcipher Set_D/mmssms.db
# PRAGMA key = '<password>';
# .tables

# Search for flags in SMS body
sqlite3 Set_D/mmssms.db "SELECT address, body FROM sms WHERE body LIKE '%flag%' OR body LIKE '%secret%';"

# Dump everything
sqlite3 Set_D/mmssms.db ".dump" > Set_D/mmssms_dump.sql
```

### 4. Analyze sample.sql
```bash
cat Set_D/sample.sql
sqlite3 /tmp/sample_D.db < Set_D/sample.sql
sqlite3 /tmp/sample_D.db ".tables"
sqlite3 /tmp/sample_D.db ".dump"
# Query all tables found
```

---

## GENERAL TOOLS QUICK REFERENCE

### File Identification
```bash
file <filename>
exiftool <filename>
xxd <filename> | head -20
```

### Strings Search
```bash
strings <file> | grep -i "flag\|password\|secret\|key\|hack\|admin"
strings -el <file>   # Little-endian UTF-16 (Windows strings)
strings -n 6 <file>  # Min 6 chars
```

### Hash Verification
```bash
md5sum <file>
sha256sum <file>
```

### Hex Editor
```bash
xxd <file> | head -50
xxd <file> | grep -i "flag"
hexdump -C <file> | head -50
```

### PDF Tools
```bash
pdf2john <file> > hash.txt          # Extract hash
john hash.txt --wordlist=rockyou.txt # Crack
qpdf --password=X --decrypt in out   # Decrypt
pdftotext <file> output.txt          # Extract text
pdfimages <file> prefix              # Extract images
pdfinfo <file>                       # Metadata
```

### SQLite
```bash
sqlite3 <db> ".tables"
sqlite3 <db> ".schema"
sqlite3 <db> ".dump"
sqlite3 <db> "SELECT * FROM <table>;"
sqlite3 -header -csv <db> "SELECT * FROM <table>;" > out.csv
```

### Disk Image / Sleuthkit
```bash
mmls <image>                      # Partition table
fsstat [-o offset] <image>        # FS info
fls [-o offset] -r -p <image>    # List all files
fls [-o offset] -r -p -d <image> # Deleted only
icat [-o offset] <image> <inode> > recovered  # Extract file
tsk_recover -e <image> output_dir/            # Recover all
```

### File Carving
```bash
foremost -t all -i <image> -o output_dir/
scalpel <image> -o output_dir/
binwalk <image>
binwalk -e <image>
photorec <image>
```

### EVTX (Windows Event Logs)
```bash
# Python script (already shown above)
# Key Event IDs:
# 4624 - Successful Logon
# 4625 - Failed Logon
# 4634 - Logoff
# 4648 - Logon with explicit credentials
# 4672 - Special privileges (admin)
# 4688 - New process created
# 4689 - Process exited
# 4697/7045 - Service installed
# 1102 - Audit log cleared
# 4720 - User account created
# 4732 - Member added to security group
```

### Timeline Analysis
```bash
fls -r -p -m "/" <image> > bodyfile.txt
mactime -b bodyfile.txt -d > timeline.csv
```

### Rockyou Wordlist Location
```bash
# Common locations:
ls /usr/share/wordlists/rockyou.txt
ls /usr/share/seclists/Passwords/Leaked-Databases/rockyou.txt
# If compressed:
gunzip /usr/share/wordlists/rockyou.txt.gz
```

---

## WORKFLOW: WHAT TO DO FIRST

1. **READ THE QUESTION PDF FIRST** - Crack the encrypted PDF → read instructions
2. **Identify evidence files** - `file *` on everything  
3. **Strings search** - Quick `strings | grep flag` on all files
4. **Analyze systematically** - Follow the set-specific steps above
5. **Document findings** - Take screenshots, save outputs
