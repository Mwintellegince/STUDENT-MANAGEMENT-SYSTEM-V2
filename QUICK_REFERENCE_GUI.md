# MWINTELLIGENCE GUI - Quick Reference

## 🎯 Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Tab` | Navigate between fields |
| `Enter` | Submit form / Confirm |
| `Esc` | Close window / Cancel |
| `Ctrl+O` | Open import dialog |
| `Ctrl+S` | Save/Export |
| `Ctrl+F` | Open search |
| `Ctrl+N` | Add new student |
| `Delete` | Delete selected student |

---

## 📋 Menu Reference

### File Menu
- **Import CSV** - Load student database from CSV file
- **Export** - Save database to CSV/JSON/RTF
- **Exit** - Save and close application

### Students Menu  
- **Add Student** - Create new student record
- **List All** - View complete student registry
- **Search** - Find students by criteria
- **Edit** - Modify selected student

### Analytics Menu
- **Statistics** - View database statistics
- **GPA Analysis** - Grade distribution
- **Reports** - Generate detailed reports

### Settings Menu
- **Preferences** - Configure system settings
- **About** - Application information

---

## 🖱️ Mouse Controls

### Main Dashboard
- **Single Click** - Select button/option
- **Double Click** - Quick access to features

### Student List
- **Single Click Row** - Select student
- **Double Click Row** - Open edit window
- **Right Click** - Context menu (future)
- **Scroll Wheel** - Scroll through list

### Forms
- **Click Field** - Start typing
- **Click Button** - Submit/Cancel
- **Drag Window** - Move window position

---

## 📝 Form Validation

### Name Field
- ✅ Required
- ✅ 1-128 characters
- ❌ Cannot be empty

### Age Field
- ✅ Number only
- ✅ Range: 16-120
- 🔄 Auto-corrects out of range

### GPA Field
- ✅ Decimal number
- ✅ Range: 0.00-4.00
- 🔄 Slider for easy input

### Email Field
- ⚠️ Optional
- ✅ Format: user@domain.com
- ⚠️ Shows error if invalid

### Phone Field
- ⚠️ Optional
- ✅ Format: +1234567890
- ⚠️ Shows error if invalid

---

## 🎨 Color Coding

### Status Colors
- 🟢 **Green** - Honor Roll (GPA ≥ 3.8)
- 🟡 **Yellow** - Dean's List (GPA ≥ 3.5)
- 🔴 **Red** - Academic Probation (GPA < 2.0)
- ⚪ **White** - Active status

### UI Colors
- 🔵 **Blue Buttons** - Primary actions
- ⚫ **Dark Background** - Main windows
- 🔷 **Cyan Headers** - Section titles

---

## 🔍 Search Tips

### By Name
```
Type: john
Finds: John Doe, Johnny Smith, Johnson
```

### By ID
```
Type: john1234
Finds: Exact ID match
```

### By Major
```
Type: computer
Finds: Computer Science, Computer Engineering
```

### Case Insensitive
All searches ignore capitalization!

---

## 📊 Statistics Explained

### Total Students
- Count of all records in database

### Average GPA
- Mean GPA across all students
- Formula: Sum(GPA) / Count

### Honor Roll %
- Students with GPA ≥ 3.8
- Percentage of total

### Academic Probation %
- Students with GPA < 2.0
- Percentage of total

### Major Distribution
- Count of students per major
- Sorted by count

---

## 💾 File Operations

### Import CSV
1. Click: File → Import CSV
2. File automatically loads from `students.csv`
3. Errors are skipped, valid records imported
4. See log for import results

### Export CSV
1. Click: File → Export
2. Enter filename (without extension)
3. Click "Export as CSV"
4. File saved to program directory

### Auto-Save
- **When**: Every time you close the app
- **File**: `students.csv`
- **Backup**: `backup_YYYY-MM-DD_HH-MM-SS.csv`

---

## ⚙️ Settings Guide

### Auto Backup
- **ON**: Creates backup after each change
- **OFF**: No automatic backups
- **Default**: ON

### Logging
- **ON**: Writes to `system.log`
- **OFF**: No logging
- **Default**: ON

### Data Validation
- **ON**: Validates email/phone formats
- **OFF**: Accepts any format
- **Default**: ON

### Max Students
- **Range**: 100 - 100,000
- **Default**: 10,000
- **Effect**: Database size limit

---

## 🐛 Troubleshooting

### Window Not Visible
- **Fix**: Check if minimized
- **Fix**: Alt+Tab to switch windows

### Form Not Submitting
- **Check**: All required fields filled
- **Check**: Email/phone format valid
- **Look**: Red error messages

### Search Not Working
- **Check**: Database has students
- **Check**: Search query spelling
- **Try**: Partial words

### Application Slow
- **Fix**: Close unused windows
- **Fix**: Reduce database size
- **Fix**: Restart application

### Data Not Saving
- **Check**: Write permission to folder
- **Check**: Disk space available
- **Check**: `students.csv` not locked

---

## 🔥 Pro Tips

### Productivity
- ✅ Use Tab to navigate forms quickly
- ✅ Keep search window open for quick lookups
- ✅ Double-click rows to edit instantly
- ✅ Use slider for GPA (faster than typing)

### Data Management
- ✅ Export regularly as backup
- ✅ Check statistics after bulk changes
- ✅ Use search before adding duplicates
- ✅ Keep notes field for important info

### Performance
- ✅ Close windows you're not using
- ✅ Search with specific terms
- ✅ Don't keep all windows open
- ✅ Restart app if sluggish

---

## 📞 Getting Help

### Check These First
1. This quick reference
2. README_GUI.md (full documentation)
3. COMPARISON.md (console vs GUI)

### Still Need Help?
- 📧 Email: support@mwintelligence.com
- 🐛 Report bugs on GitHub
- 💡 Request features on GitHub

---

## 🎓 Example Workflows

### Adding Multiple Students
```
1. Open "Add Student" window
2. Fill first student form
3. Click "Add Student" (form clears)
4. Fill next student form
5. Repeat until done
6. Close window
```

### Finding At-Risk Students
```
1. Click "View Statistics"
2. Check "Academic Probation" count
3. Close statistics
4. Open "Search"
5. Search by low GPA range
6. Review results
```

### Bulk Export
```
1. Click File → Export
2. Enter filename: "class_2025"
3. Click "Export as CSV"
4. Open file in Excel
5. Analyze or print
```

---

**Last Updated: October 24, 2025**

*For complete documentation, see README_GUI.md*
