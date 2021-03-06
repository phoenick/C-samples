﻿README

mycache

A simple Least Recently Used cache system that stores telephone records.
Developed in C but with some C++ syntactic conveniences.
The code is organised using the First-Class ADT pattern.
Costs of:
-Record retrieval from cache: O(1)
-Record deletion from cache : O(1)
-LRU preservance for a record in cache: O(k) where k the number of records in cache.

Στην ανάπτυξη του προγράμματος χρησιμοποιήθηκε η γλώσσα C, ωστόσο τα αρχεία
κώδικα έχουν κατάληξη .cpp και μεταγλωτίζονται με g++ επειδή γίνεται χρήση μερικών
ευκολιών της C++ (όπως η δήλωση μεταβλητών σε οποιδήποτε σημείο ενός μπλοκ
κώδικα).
Ο κώδικας οργανώνεται σε τρία τμήματα καθένα από τα οποία έχει κάποιοες βασικές
δομές οι οποίες ακολουθούν το μοτίβο First-Class ADT ώστε να μην μπορούν να
τροποποιηθούν κατα βούληση, αλλά να χρησιμοποιηθούν μόνο μέσω των παρεχόμενων
συναρτήσεων, που εξασφαλίζουν σε ένα βαθμό την ορθή χρήση τους.
Το πρώτο τμήμα αφορά μια διπλή δυναμικη λίστα (LruList) η οποία φυλάει κόμβους, ο
καθένας από τους οποίους κρατάει μια εγγραφή (χωρισμένη σε δύο κομμάτια : α)το phone
number και β)τις υπόλοιπες πληροφορίες). Η ιδέα είναι ότι η θέση ενός κόμβου στην
λίστα δηλώνει την σειρά χρήσης του, έτσι ώστε ο πρώτος κόμβος (first) να είναι αυτός
που χρησιμοποιήθηκε πιο πρόσφατα και ο τελευταίος (last) ο least recently used. Έτσι
όταν χρησιμοποιέιται ένας ενδιάμεσος κόμβος, μεταφέρεται στην πρώτη θέση της λίστας,
ενώ ο least recently used βρίσκεται πάντα στην τελευταία.
Το δεύτερο τμήμα είναι ο πίνακας Hash, κάθε κελί του οποίου δείχνει σε έναν κόμβο της
παραπάνω λίστας. Η Hash Function που χρησιμοποιείται είναι πολύ απλή (mod size),
ωστόσο στην επίλυση των συγκρούσεων χρησιμοποιείται quadratic probing, οπότε σε
συνδιασμό με την τυχαιότητα των τηλεφωνικών αριθμών πιστεύουμε ότι θα λειτουργήσει
καλά.
Το τρίτο τμήμα λέγεται cache και είναι ουσιαστικά ένα επίπεδο που χρησιμοποιεί και
συνδιάζει τις παραπάνω δομές για να δημιουργήσει ένα ολοκληρωμένο σύστημα cache,
παρέχοντας και ένα από interface για την χρήση του.
Τέλος η main κάνει χρήση μόνο του τμήματος cache και παρέχει τη διασύνδεση (γραμμή
εντολών) του χρήστη με το cache σύστημα.