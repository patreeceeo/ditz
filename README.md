Ditz
====
The stupid (stupid as in simple) DBMS

The basic idea behind Ditz is that of a "lazy table," which is a data structure that that insists on holding its contents in a tabular format, but is otherwise up for whatever. Ditz is nothing more that an attempt to build a complete DBMS using little more than "lazy tables." There are two motivations behind this approach: One is that it makes the entire system very comprehensible and the other is that such a design makes it easy to strip away all but the parts that you really need if you're concerned about speed/memory usage.

Actually I sort of lied when I said that a "lazy table" only requires its contents to be in a tabular format, it also only allows each record to be one of two data-types: NATURAL (as in the natural numbers) or STRING. Every other data-type must be somehow encoded into one of these two essential data types. Theoretically, these tables could be even lazier by only accepting one of the two, but given the static typing of C++, its just convenient to support both.

The way that a complete DBMS could be built using little more that lazy tables is to designate certain tables as "meta," meaning they contain information about other tables. Indexes, foreign keys, triggers, views, etc. can all be modeled with lazy tables that reference rows, columns, records, or other tables.

I know its a bit crazy to want to design my own DBMS. This is a just-for-fun projects that is still very much a work-in-progress.

