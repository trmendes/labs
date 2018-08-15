import Link from 'next/link';

const Index = () => (
    <section>
        <h1>Hello world from Next JS</h1>
        <Link href="/about">
            <a title="About NextJS">About this Project</a>
        </Link>
    </section>
);

export default Index;
