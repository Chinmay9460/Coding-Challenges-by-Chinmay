# System Design Interview Preparation Guide

## Fundamentals (10)
1. **Client-Server Architecture** - Basic model of distributed computing
2. **Network Protocols** - HTTP/HTTPS, TCP/IP, UDP, WebSockets
3. **REST API Design** - Principles, best practices, versioning
4. **Databases** - Relational vs NoSQL, indexing, ACID properties
5. **Caching** - Client-side, CDN, application caching, database caching
6. **Load Balancing** - Algorithms, health checks, session persistence
7. **Proxies** - Forward vs reverse proxies, use cases
8. **CAP Theorem** - Consistency, Availability, Partition tolerance trade-offs
9. **Horizontal vs Vertical Scaling** - When to use each approach
10. **Microservices vs Monolithic Architecture** - Pros, cons, implementation

## Distributed Systems (15)
1. **Consistent Hashing** - Load distribution, minimizing redistribution
2. **Service Discovery** - Methods, tools (Consul, etcd, ZooKeeper)
3. **Distributed Consensus** - Paxos, Raft algorithms
4. **Distributed Transactions** - Two-phase commit, saga pattern
5. **Idempotency** - Ensuring operations can be repeated safely
6. **Failure Detection** - Heartbeats, Phi Accrual algorithm
7. **Circuit Breaking** - Preventing cascading failures
8. **Distributed Caching** - Redis, Memcached architectures
9. **Message Queues** - Kafka, RabbitMQ, SQS implementation
10. **Event Sourcing** - Storing state changes as events
11. **CQRS** - Command query responsibility segregation
12. **Sharding Strategies** - Range, hash, directory-based sharding
13. **Replication Models** - Master-slave, multi-master, quorum-based
14. **Eventual Consistency** - Models and reconciliation techniques
15. **Distributed Locking** - Implementations and challenges

## Databases and Storage (15)
1. **SQL Database Design** - Normalization, indexing strategies, query optimization
2. **NoSQL Types** - Document, key-value, column-family, graph databases
3. **Database Partitioning** - Horizontal vs vertical partitioning
4. **Index Design** - B-trees, hash indexes, composite indexes
5. **ACID vs BASE** - Transaction models for different databases
6. **Data Warehousing** - OLTP vs OLAP, star schema
7. **Time Series Databases** - InfluxDB, TimescaleDB design patterns
8. **Object Storage** - S3, Blob storage architecture
9. **Blockchain Storage** - Distributed ledger technologies
10. **Database Caching Strategies** - Read-through, write-through, cache invalidation
11. **Change Data Capture** - Real-time data integration patterns
12. **Hot/Warm/Cold Storage** - Tiered storage architectures
13. **Polyglot Persistence** - Using multiple database types
14. **NewSQL** - Combining SQL and NoSQL characteristics
15. **Database Migration Strategies** - Zero-downtime migrations

## Scalability Patterns (10)
1. **Read Replicas** - Scaling read operations
2. **Command Query Responsibility Segregation (CQRS)** - Separating read and write models
3. **Materialized Views** - Precomputing query results
4. **Data Denormalization** - Trading consistency for performance
5. **Database Sharding** - Horizontal partitioning strategies
6. **Queue-Based Load Leveling** - Handling traffic spikes
7. **Static Content Hosting** - Offloading static assets
8. **Compute Partitioning** - Function-based, service-based, geographical
9. **Throttling and Rate Limiting** - Protecting services from overload
10. **Bulkhead Pattern** - Isolating system components

## Reliability Patterns (10)
1. **Circuit Breaker Pattern** - Failing fast to prevent cascading failures
2. **Retry with Exponential Backoff** - Handling transient failures
3. **Timeout Handling** - Preventing indefinite waiting
4. **Graceful Degradation** - Providing reduced functionality under load
5. **Feature Flags** - Controlling feature availability
6. **Chaos Engineering** - Testing system resilience
7. **Blue-Green Deployment** - Zero-downtime deployments
8. **Canary Releases** - Incremental rollouts
9. **Health Check API** - Monitoring application health
10. **Disaster Recovery Planning** - RPO, RTO, failover strategies

## Security Design (10)
1. **Authentication Systems** - OAuth, JWT, SSO implementations
2. **Authorization Models** - RBAC, ABAC, capability-based security
3. **API Security** - Rate limiting, input validation, output encoding
4. **Data Encryption** - At rest, in transit, end-to-end
5. **HTTPS Implementation** - TLS/SSL configuration
6. **DDOS Protection** - Strategies and implementations
7. **Cross-Origin Resource Sharing (CORS)** - Secure cross-domain requests
8. **Secrets Management** - Vault, key management services
9. **Input Validation** - Preventing injection attacks
10. **Security Monitoring** - Intrusion detection, audit logging

## Common System Design Interview Problems (20)
1. **URL Shortener** - Design TinyURL
2. **Social Media Feed** - Design Facebook/Twitter timeline
3. **Chat Application** - Design WhatsApp/Messenger
4. **Video Streaming Service** - Design YouTube/Netflix
5. **Rate Limiter** - Design API rate limiting system
6. **Web Crawler** - Design Google's web crawler
7. **Search Autocomplete** - Design type-ahead suggestion system
8. **Distributed File Storage** - Design Google Drive/Dropbox
9. **Notification System** - Design push notification service
10. **Payment System** - Design Stripe/PayPal
11. **E-commerce Platform** - Design Amazon's backend
12. **Ride Sharing Service** - Design Uber/Lyft
13. **Hotel Booking System** - Design Booking.com/Airbnb
14. **Online Gaming Service** - Design multiplayer game platform
15. **Content Delivery Network** - Design CDN architecture
16. **Distributed Cache** - Design Redis-like system
17. **Ad Serving System** - Design targeted advertising platform
18. **Social Graph** - Design Facebook's social graph
19. **Distributed Task Scheduler** - Design cron-like system
20. **Real-time Analytics Platform** - Design analytics dashboard

## System Design Methodology (5)
1. **Requirements Clarification** - Functional and non-functional requirements
2. **Back-of-the-envelope Calculations** - Estimating scale and resources
3. **System Interface Definition** - API design and contracts
4. **Data Model Design** - Entity relationships and schema
5. **High-level Component Design** - Architecture diagram and component interactions

## Advanced Topics (10)
1. **Distributed Tracing** - Implementing observability across services
2. **Graph Database Design** - Social networks, recommendation systems
3. **Machine Learning Infrastructure** - Model training and serving architecture
4. **Serverless Architecture** - FaaS design patterns
5. **Edge Computing** - Moving computation closer to data sources
6. **Real-time Processing** - Stream processing architectures
7. **Blockchain Systems** - Distributed ledger architecture
8. **Multi-region Architecture** - Global distribution strategies
9. **IoT Backend Design** - Handling millions of connected devices
10. **Zero-trust Architecture** - Security design beyond perimeter model

## Practical Tools and Technologies (5)
1. **Container Orchestration** - Kubernetes architecture and patterns
2. **Service Mesh** - Istio, Linkerd implementation
3. **API Gateway** - Design patterns and implementations
4. **Monitoring and Observability** - Prometheus, Grafana, ELK stack
5. **Infrastructure as Code** - Terraform, CloudFormation patterns
